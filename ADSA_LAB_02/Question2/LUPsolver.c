#include <stdio.h>
#include <math.h>
#include "munit.h"

#define N 3
#define EPS 1e-9

// ---------- Helper Functions ----------
void swap_rows(double A[N][N], int P[N], int r1, int r2) {
    for (int j = 0; j < N; j++) {
        double tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    int t = P[r1]; P[r1] = P[r2]; P[r2] = t;
}

int lup_decompose(double A[N][N], int P[N]) {
    for (int i = 0; i < N; i++) P[i] = i;

    for (int k = 0; k < N; k++) {
        int pivot = k;
        double maxval = fabs(A[k][k]);
        for (int i = k + 1; i < N; i++) {
            if (fabs(A[i][k]) > maxval) {
                maxval = fabs(A[i][k]);
                pivot = i;
            }
        }
        if (maxval < EPS) return 0; // singular

        if (pivot != k) swap_rows(A, P, k, pivot);

        for (int i = k + 1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < N; j++)
                A[i][j] -= A[i][k] * A[k][j];
        }
    }
    return 1;
}

void lup_solve(double A[N][N], int P[N], double b[N], double x[N]) {
    double y[N];

    for (int i = 0; i < N; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++)
            y[i] -= A[i][j] * y[j];
    }

    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}

// ---------- Test Cases ----------
static MunitResult test_lup_1(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {2, -1, 1},
        {3, 3, 9},
        {3, 3, 5}
    };
    double b[N] = {2, -1, 4};
    double x[N];
    int P[N];

    int status = lup_decompose(A, P);
    munit_assert_int(status, ==, 1);

    lup_solve(A, P, b, x);

    double expected[N] = {1.0, 2.0, -1.0};
    for (int i = 0; i < N; i++)
        munit_assert_double(x[i], ==, expected[i]);

    return MUNIT_OK;
}

static MunitResult test_lup_2(const MunitParameter params[], void* data) {
    double A[N][N] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    double b[N] = {6, 5, 4};
    double x[N];
    int P[N];

    int status = lup_decompose(A, P);
    munit_assert_int(status, ==, 1);

    lup_solve(A, P, b, x);

    double expected[N] = {2.0, 1.0, 1.0};
    for (int i = 0; i < N; i++)
        munit_assert_double(x[i], ==, expected[i]);

    return MUNIT_OK;
}

// ---------- MUnit Suite ----------
static MunitTest tests[] = {
    {"/lup_test1", test_lup_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/lup_test2", test_lup_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite suite = {
    "lup-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
