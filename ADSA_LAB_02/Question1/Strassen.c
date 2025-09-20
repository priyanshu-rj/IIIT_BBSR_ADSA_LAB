#include <stdio.h>
#include "munit.h"

#define MAX 8

// ---------- Matrix Operations ----------
void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// ---------- Strassen Multiplication ----------
void strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 2) {
        int a11 = A[0][0], a12 = A[0][1], a21 = A[1][0], a22 = A[1][1];
        int b11 = B[0][0], b12 = B[0][1], b21 = B[1][0], b22 = B[1][1];

        int M1 = (a11 + a22) * (b11 + b22);
        int M2 = (a21 + a22) * b11;
        int M3 = a11 * (b12 - b22);
        int M4 = a22 * (b21 - b11);
        int M5 = (a11 + a12) * b22;
        int M6 = (a21 - a11) * (b11 + b12);
        int M7 = (a12 - a22) * (b21 + b22);

        C[0][0] = M1 + M4 - M5 + M7;
        C[0][1] = M3 + M5;
        C[1][0] = M2 + M4;
        C[1][1] = M1 - M2 + M3 + M6;
        return;
    }

    int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Split matrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    add(k, A11, A22, temp1);
    add(k, B11, B22, temp2);
    strassen(k, temp1, temp2, M1);

    add(k, A21, A22, temp1);
    strassen(k, temp1, B11, M2);

    sub(k, B12, B22, temp2);
    strassen(k, A11, temp2, M3);

    sub(k, B21, B11, temp2);
    strassen(k, A22, temp2, M4);

    add(k, A11, A12, temp1);
    strassen(k, temp1, B22, M5);

    sub(k, A21, A11, temp1);
    add(k, B11, B12, temp2);
    strassen(k, temp1, temp2, M6);

    sub(k, A12, A22, temp1);
    add(k, B21, B22, temp2);
    strassen(k, temp1, temp2, M7);

    add(k, M1, M4, temp1);
    sub(k, temp1, M5, temp2);
    add(k, temp2, M7, C11);

    add(k, M3, M5, C12);
    add(k, M2, M4, C21);

    sub(k, M1, M2, temp1);
    add(k, temp1, M3, temp2);
    add(k, temp2, M6, C22);

    // Combine results
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// ---------- Helper Function ----------
void printMatrix(int n, int M[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

// ---------- MUnit Test Cases ----------
static MunitResult test_strassen_2x2(const MunitParameter params[], void* user_data) {
    int A[MAX][MAX] = {{1, 2}, {3, 4}};
    int B[MAX][MAX] = {{5, 6}, {7, 8}};
    int C[MAX][MAX];

    strassen(2, A, B, C);

    int expected[MAX][MAX] = {{19, 22}, {43, 50}};
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            munit_assert_int(C[i][j], ==, expected[i][j]);

    return MUNIT_OK;
}

static MunitResult test_strassen_4x4(const MunitParameter params[], void* user_data) {
    int A[MAX][MAX] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };
    int B[MAX][MAX] = {
        {16,15,14,13},
        {12,11,10,9},
        {8,7,6,5},
        {4,3,2,1}
    };
    int C[MAX][MAX];

    strassen(4, A, B, C);

    int expected[MAX][MAX] = {
        {80,70,60,50},
        {240,214,188,162},
        {400,358,316,274},
        {560,502,444,386}
    };

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            munit_assert_int(C[i][j], ==, expected[i][j]);

    return MUNIT_OK;
}

// ---------- Test Suite ----------
static MunitTest tests[] = {
    {"/strassen_2x2", test_strassen_2x2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/strassen_4x4", test_strassen_4x4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "strassen-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

// ---------- Main ----------
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
