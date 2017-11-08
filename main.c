#include <stdio.h>
#include <windows.h>
#include "functions.h"

/**
 Parallel and distributed computing.
 Lab 4. Threads in WinAPI
 Lisovyi Volodymyr
 IO-53
 30.10.17
 F1: e = (A*B) + (C*(D*(MA*MD)))
 F2: ML = SORT(MF + MG*MH)
 F3: O = MAX(MP*MR)*T
 */
int main() {
    printf("Main start\n");

    HANDLE hThread[3];
    DWORD Tid1, Tid2, Tid3;

    hThread[0] = CreateThread(NULL, 300000000, (LPTHREAD_START_ROUTINE)threadFunction3,
                              NULL, 0, &Tid1);
    hThread[1] = CreateThread(NULL, 300000000, (LPTHREAD_START_ROUTINE)threadFunction2,
                              NULL, CREATE_SUSPENDED, &Tid2);
    hThread[2] = CreateThread(NULL, 300000000, (LPTHREAD_START_ROUTINE)threadFunction1,
                              NULL, 0, &Tid3);

    SetThreadPriority(hThread[0], THREAD_PRIORITY_BELOW_NORMAL);
    SetThreadPriority(hThread[1], THREAD_PRIORITY_ABOVE_NORMAL);
    SetThreadPriority(hThread[2], THREAD_PRIORITY_HIGHEST);
    ResumeThread(hThread[1]);
    WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
    for (int i = 0; i < 3; i++) {
        CloseHandle(hThread[i]);
    }

    printf("Main finish\n");
    return 0;
}

