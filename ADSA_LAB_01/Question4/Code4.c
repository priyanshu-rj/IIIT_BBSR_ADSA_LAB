#include <stdio.h>
#include <stdlib.h>
#include "munit.h"

// ---------------- Heap Sort Implementation ----------------
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// ---------------- Helper Function ----------------
static void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ---------------- Unit Tests ----------------
static MunitResult test_sorted_array(const MunitParameter params[], void* user_data) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    for (int i = 0; i < n; i++) {
        munit_assert_int(arr[i], ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_reverse_array(const MunitParameter params[], void* user_data) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    for (int i = 0; i < n; i++) {
        munit_assert_int(arr[i], ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_unsorted_array(const MunitParameter params[], void* user_data) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int expected[] = {5, 6, 7, 11, 12, 13};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    for (int i = 0; i < n; i++) {
        munit_assert_int(arr[i], ==, expected[i]);
    }
    return MUNIT_OK;
}

static MunitResult test_single_element(const MunitParameter params[], void* user_data) {
    int arr[] = {42};
    int expected[] = {42};
    int n = 1;

    heapSort(arr, n);

    munit_assert_int(arr[0], ==, expected[0]);
    return MUNIT_OK;
}

static MunitResult test_duplicates(const MunitParameter params[], void* user_data) {
    int arr[] = {4, 1, 3, 1, 4, 2};
    int expected[] = {1, 1, 2, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    for (int i = 0; i < n; i++) {
        munit_assert_int(arr[i], ==, expected[i]);
    }
    return MUNIT_OK;
}

// ---------------- Test Suite ----------------
static MunitTest tests[] = {
    { (char*) "/sorted_array", test_sorted_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/reverse_array", test_reverse_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/unsorted_array", test_unsorted_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/single_element", test_single_element, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/duplicates", test_duplicates, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    (char*) "heap-sort-tests", /* name */
    tests,                     /* tests */
    NULL,                      /* suites */
    1,                         /* iterations */
    MUNIT_SUITE_OPTION_NONE    /* options */
};

// ---------------- Main ----------------
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
