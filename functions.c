//
// Created by Foresstt on 28-Oct-17.
//

#include "functions.h"
#include <stdio.h>
#include <limits.h>
#include <windows.h>;

const int n   = 3;
const int num = 1;

void printVector(int *A) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void printMatrix(int A[][n]) {
    for (int i = 0; i < n; i++) {
        printVector(A[i]);
        printf("\n");
    }
    printf("\n");
}

void fillVector(int num, int *A) {
    for (int i = 0; i < n; i++)
        A[i] = num;
}

void fillMatrix(int num, int A[][n]) {
    for (int i = 0; i < n; i++) {
        fillVector(num, A[i]);
    }
}
/**
 * Multiplication matrix A and B
 * @param A - matrix
 * @param B - matrix
 * @param C=A*B - matrix
 */
void matrixMultiplication(int A[][n], int B[][n], int C[][n]) {

    int M[n][n];
    int buf;
    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            buf = 0;
            for (int k = 0; k < n; k++) {
                buf += A[i][k] * B[k][j];
            }
            M[i][j] = buf;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = M[i][j];
}

/**
 * Multiplication vector A with matrix B
 * @param A - vector
 * @param B - matrix
 * @param C=A*B - vector
 */
void vectorMatrixMultiplication(int *A, int B[][n], int *C) {
    int M[n];
    int buf;
    for (int i = 0; i < n; i++ ) {
        buf = 0;
        for (int j = 0; j < n; j++) {
            buf += A[j] * B[j][i];
        }
        M[i] = buf;
    }
    for (int i = 0; i < n; i++)
        C[i] = M[i];
}

/**
 * Calculate scalar of A with B
 * @param A - vector
 * @param B - vector
 * @param scalar=A*B - number
 */
int scalar(int *A, int *B) {
    int scalar = 0;
    for (int i = 0; i < n; i++) {
        scalar += A[i] * B[i];
    }
    return scalar;
}




/**
 * Add matrix A and B
 * @param A - matrix
 * @param B - matrix
 * @param C=A+B
 */
void matrixAddition(int A[][n], int B[][n], int C[][n]) {

    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

}

/**
 * Multiplication vector A with number num
 * @param num
 * @param A
 * @param B=num*A - vector
 */
void numberVectorMultiplication(int num, int *A, int *B) {
    for (int i = 0; i < n; i++)
        B[i] = A[i] * num;
}

/**
 * Find max element from matrix
 * @param A - matrix
 * @param max element
 */
int matrixMax(int A[][n]) {
    int max = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] > max) {
                max = A[i][j];
            }
        }
    }

    return max;
}

/**
 * Sort matrix A
 * @param A - matrix
 */
void matrixSort(int A[][n]) {
    int index = 0;
    int max   = 0;
    for (int line = 0; line < n; line++) {
        for (int i = 0; i < n; i++) {
            index = i;
            max   = A[line][i];
            for (int j = i + 1; j < n; j++) {
                if (A[line][j] > max) {
                    index = j;
                    max   = A[line][j];
                }
            }
            A[line][index] = A[line][i];
            A[line][i]     = max;
        }
    }
}

/**
  * F1: e = (A*B) + (C*(D*(MA*MD)))
  */
void threadFunction1() {
    printf("Thread1 start\n");
    int MA[n][n];
    int MD[n][n];
    int a[n];
    int b[n];
    int c[n];
    int d[n];

    fillVector(num, a);
    fillVector(num, b);
    fillVector(num, c);
    fillVector(num, d);
    fillMatrix(num, MA);
    fillMatrix(num, MD);

    Sleep(1000);
    matrixMultiplication(MA, MD, MA);
    vectorMatrixMultiplication(d, MA, d);
    int e = scalar(a, b) + scalar(c, d);
    Sleep(1000);

    if (n < 7) {
        printf("T1: e = %d\n", e);
    }

    printf("Thread1 finish\n");
}

/**
  * F2: ML = SORT(MF + MG*MH)
  */
void threadFunction2() {
    printf("Thread2 start\n");
    int ML[n][n];
    int MF[n][n];
    int MG[n][n];
    int MH[n][n];

    fillMatrix(num, MF);
    fillMatrix(num, MG);
    fillMatrix(num, MH);

    Sleep(2000);

    matrixMultiplication(MG, MH, ML);
    matrixAddition(ML, MF, ML);
    matrixSort(ML);
    Sleep(2000);
    if (n < 7) {
        printf("T2: ML =\n");
        printMatrix(ML);
    }


    printf("Thread2 finish\n");
}

/**
  * F3: O = MAX(MP*MR)*T
  */
void threadFunction3() {
    printf("Thread3 start\n");
    int MP[n][n];
    int MR[n][n];
    int T[n];
    int O[n];

    fillMatrix(num, MP);
    fillMatrix(num, MR);
    fillVector(num, T);

    Sleep(500);
    matrixMultiplication(MP, MR, MP);
    numberVectorMultiplication(matrixMax(MP), T, O);
    Sleep(500);

    if (n < 7) {
        printf("T3: O = ");
        printVector(O);
    }

    printf("Thread3 finish\n");
}