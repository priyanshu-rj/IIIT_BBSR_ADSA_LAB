#include <stdio.h>
#include <math.h>
#include "munit.h"   // Include munit header

#define N 1039467

// Original functions
double f1(int n) { return 1.0 / n; }
double f2(int n) { return log2(n); }
double f3(int n) { return 12 * sqrt(n); }
double f4(int n) { return 50 * sqrt(n); }
double f5(int n) { return pow(n, 0.51); }
double f6(int n) { return n * log2(n); }
double f7(int n) { return (double)n * n - 324; }
double f8(int n) { return 100.0 * n * n + 6 * n; }
double f9(int n) { return 2.0 * pow(n, 3); }
double f10(int n) { return pow(n, log2(n)); }
double f11(int n) { return pow(3, n); }
double f12(int n) { return pow(2, n); }

// ---------------------- TEST CASES ----------------------

// Test f1
static MunitResult test_f1(const MunitParameter params[], void* data) {
    double result = f1(10);
    munit_assert_double(result, ==, 0.1);
    return MUNIT_OK;
}

// Test f2
static MunitResult test_f2(const MunitParameter params[], void* data) {
    double result = f2(8); // log2(8) = 3
    munit_assert_double(result, ==, 3.0);
    return MUNIT_OK;
}

// Test f3
static MunitResult test_f3(const MunitParameter params[], void* data) {
    double result = f3(4); // 12*sqrt(4)=24
    munit_assert_double(result, ==, 24.0);
    return MUNIT_OK;
}

// Test f6
static MunitResult test_f6(const MunitParameter params[], void* data) {
    double result = f6(16); // 16*log2(16)=16*4=64
    munit_assert_double(result, ==, 64.0);
    return MUNIT_OK;
}

// Add more tests for other functions as needed...

// ---------------------- REGISTER TESTS ----------------------

static MunitTest tests[] = {
    { "/test_f1", test_f1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f2", test_f2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f3", test_f3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_f6", test_f6, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // Add other test functions here...
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/my-tests",   // Suite name
    tests,         // The tests to run
    NULL,          // No sub-suites
    1,             // Iterations
    MUNIT_SUITE_OPTION_NONE
};

// ---------------------- MAIN ----------------------

int main(int argc, char* argv[]) {
    // Run unit tests
    return munit_suite_main(&suite, NULL, argc, argv);
}
