#include <stdio.h>
#include "munit.h"   // make sure munit.h is in same directory

// ---------------- Function: Find defective coin ----------------
int find(int arr[], int n) {
    int low = 0, high = n - 1;

    while (low <= high) {
        if (arr[low] < arr[high]) {
            return arr[low];
        }
        int mid = low + (high - low) / 2;

        if ((mid == 0 || arr[mid] < arr[mid - 1]) &&
            (mid == n - 1 || arr[mid] < arr[mid + 1])) {
            return arr[mid];
        }
        if (low > 0 && arr[low] < arr[low - 1]) {
            mid = low - 1;
        } else {
            low = low + 1;
        }

        if ((low == 0 || arr[low] < arr[low - 1]) &&
            (low == n - 1 || arr[low] < arr[low + 1])) {
            return arr[low];
        }

        if (low > 0 && arr[low] < arr[low - 1]) {
            mid = low - 1;
        } else {
            low = low + 1;
        }
    }
    return -1;
}

// ---------------------- TEST CASES ----------------------

// Case 1: Defective coin exists in middle
static MunitResult test_coin_middle(const MunitParameter params[], void* data) {
    int arr[] = {5, 6, 1, 7, 8};
    int result = find(arr, 5);
    munit_assert_int(result, ==, 1);
    return MUNIT_OK;
}

// Case 2: Defective coin is the first element
static MunitResult test_coin_first(const MunitParameter params[], void* data) {
    int arr[] = {2, 3, 4, 5};
    int result = find(arr, 4);
    munit_assert_int(result, ==, 2);
    return MUNIT_OK;
}

// Case 3: Defective coin is the last element
static MunitResult test_coin_last(const MunitParameter params[], void* data) {
    int arr[] = {10, 20, 30, 1};
    int result = find(arr, 4);
    munit_assert_int(result, ==, 1);
    return MUNIT_OK;
}

// Case 4: No defective coin (strictly increasing)
static MunitResult test_no_defect(const MunitParameter params[], void* data) {
    int arr[] = {1, 2, 3, 4, 5};
    int result = find(arr, 5);
    // Depending on your logic, it might return 1 (the smallest)
    munit_assert_int(result, ==, 1);
    return MUNIT_OK;
}

// ---------------------- REGISTER TESTS ----------------------
static MunitTest tests[] = {
    { "/coin/middle", test_coin_middle, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/coin/first", test_coin_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/coin/last", test_coin_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/coin/no_defect", test_no_defect, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/coin-suite",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

// ---------------------- MAIN ----------------------
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
