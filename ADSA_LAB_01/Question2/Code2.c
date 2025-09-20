#include <stdio.h>
#include "munit.h"   // download munit.h and include it

// ---------------- Binary & Ternary Search ----------------
int TernarySearch(int arr[], int min, int high, int x, int *count1) {
    while (min <= high) {
        int mid1 = min + (high - min) / 3;
        int mid2 = high - (high - min) / 3;

        (*count1)++;
        if (arr[mid1] == x) {
            return mid1;
        }

        (*count1)++;
        if (arr[mid2] == x) {
            return mid2;
        }

        if (x < arr[mid1]) {
            high = mid1 - 1;
        }
        else if (x > arr[mid2]) {
            min = mid2 + 1;
        }
        else {
            min = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

int BinarySearch(int arr[], int min, int high, int x, int *count2) {
    while (min <= high) {
        int mid = min + (high - min) / 2;

        (*count2)++;
        if (arr[mid] == x) {
            return mid;
        }

        if (arr[mid] < x) {
            min = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// ---------------------- TEST CASES ----------------------

// Test both searches when element exists
static MunitResult test_search_found(const MunitParameter params[], void* data) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    int count1 = 0, count2 = 0;
    int key = 7;

    int tResult = TernarySearch(arr, 0, n - 1, key, &count1);
    int bResult = BinarySearch(arr, 0, n - 1, key, &count2);

    // Check index correctness
    munit_assert_int(tResult, ==, 3);  // index of 7
    munit_assert_int(bResult, ==, 3);

    // Check that comparisons happened (non-zero)
    munit_assert_int(count1 > 0, ==, 1);
    munit_assert_int(count2 > 0, ==, 1);

    return MUNIT_OK;
}

// Test both searches when element is not found
static MunitResult test_search_not_found(const MunitParameter params[], void* data) {
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    int count1 = 0, count2 = 0;
    int key = 7;

    int tResult = TernarySearch(arr, 0, n - 1, key, &count1);
    int bResult = BinarySearch(arr, 0, n - 1, key, &count2);

    munit_assert_int(tResult, ==, -1);
    munit_assert_int(bResult, ==, -1);

    return MUNIT_OK;
}

// Test edge case: searching first element
static MunitResult test_search_first_element(const MunitParameter params[], void* data) {
    int arr[] = {5, 10, 15, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    int count1 = 0, count2 = 0;
    int key = 5;

    int tResult = TernarySearch(arr, 0, n - 1, key, &count1);
    int bResult = BinarySearch(arr, 0, n - 1, key, &count2);

    munit_assert_int(tResult, ==, 0);
    munit_assert_int(bResult, ==, 0);

    return MUNIT_OK;
}

// ---------------------- REGISTER TESTS ----------------------
static MunitTest tests[] = {
    { "/test_search_found", test_search_found, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_search_not_found", test_search_not_found, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_search_first_element", test_search_first_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/search-suite",   // Suite name
    tests,             // The tests to run
    NULL,              // No sub-suites
    1,                 // Iterations
    MUNIT_SUITE_OPTION_NONE
};

// ---------------------- MAIN ----------------------
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
