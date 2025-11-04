#include <stdio.h>

// Recursive Binary Search
int recursiveBinarySearch(int arr[], int low, int high, int key) {
    if (low > high)
        return -1;

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;
    else if (arr[mid] > key)
        return recursiveBinarySearch(arr, low, mid - 1, key);
    else
        return recursiveBinarySearch(arr, mid + 1, high, key);
}

// Non-Recursive Binary Search
int nonRecursiveBinarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main() {
    int arr[100], n, key, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d sorted integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the key to search: ");
    scanf("%d", &key);

    int res1 = recursiveBinarySearch(arr, 0, n - 1, key);
    int res2 = nonRecursiveBinarySearch(arr, n, key);

    if (res1 != -1)
        printf("Recursive: Element found at index %d\n", res1);
    else
        printf("Recursive: Element not found\n");

    if (res2 != -1)
        printf("Non-Recursive: Element found at index %d\n", res2);
    else
        printf("Non-Recursive: Element not found\n");

    return 0;
}
