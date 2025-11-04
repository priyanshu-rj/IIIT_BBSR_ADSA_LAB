#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int medianOfThree(int arr[], int low, int high) {
    int mid = (low + high) / 2;

    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);

    return arr[mid];
}

int partition(int arr[], int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low - 1;

    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortMedian(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortMedian(arr, low, pi - 1);
        quickSortMedian(arr, pi + 1, high);
    }
}

int main() {
    int arr[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    quickSortMedian(arr, 0, n - 1);

    printf("Sorted array using Quick Sort (Median Pivot): ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
