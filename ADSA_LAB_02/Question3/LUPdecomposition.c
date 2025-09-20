#include <stdio.h>
#include <math.h>
#include "munit.h"

#define N 3
#define EPS 1e-6  // tolerance for floating-point comparison

// LUP decomposition function
int lup_decompose(double A[N][N], int P[N]) {
    int i, j, k, pivot;
    double maxA, absA, temp;

    for (i = 0; i < N; i++) P[i] = i;

    for (i = 0; i < N; i++) {
        maxA = 0.0;
        pivot = i;
        for (k = i; k < N; k++) {
            absA = fabs(A[k][i]);
            if (absA > maxA) {
                maxA = absA;
                pivot = k;
            }
        }
        if (maxA < 1e-12) return 0;  // singular

        if (pivot != i) {
            int tmp = P[i]; P[i] = P[pivot]; P[pivot] = tmp;
            for (j = 0; j < N; j++) {
                temp = A[i][j]; A[i][j] = A[pivot][j]; A[pivot][j] = temp;
            }
        }

        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];
            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }
    return 1;
}

// Test case 1: simple 3x3 matrix
static char* test_lup_simple(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {2, 1, 1},
        {4, -6, 0},
        {-2, 7, 2}
    };
    int P[N];
    int status = lup_decompose(A, P);
    munit_assert_int(status, ==, 1);

    // Check pivot array
    int expected_P[N] = {0, 2, 1};
    for (int i = 0; i < N; i++)
        munit_assert_int(P[i], ==, expected_P[i]);

    return NULL;
}

// Test case 2: singular matrix
static char* test_lup_singular(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {1, 2, 3},
        {2, 4, 6},
        {3, 6, 9}
    };
    int P[N];
    int status = lup_decompose(A, P);
    munit_assert_int(status, ==, 0);  // Should detect singular
    return NULL;
}

// List of tests
static MunitTest test_suite_tests[] = {
    {"/lup/simple", test_lup_simple, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/lup/singular", test_lup_singular, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

// Test suite
static const MunitSuite test_suite = {
    "/lup",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
