// Ternary Search and Binary Search Comprision
#include <stdio.h>

int TernarySearch(int arr[], int min, int high, int x, int *count1) {
    while (min <= high) {
        int mid1 = min + (high - min) / 3;
        int mid2 = high - (high - min) / 3;

        (*count1)++;
        if (arr[mid1] == x) {
            printf("Index Found at Index : %d", mid1);
            printf("\nTernarySearch Comparisons : %d\n", *count1);
            return mid1;
        }

        (*count1)++;  
        if (arr[mid2] == x) {
            printf("Index Found at Index : %d", mid2);
            printf("\nTernarySearch Comparisons : %d\n", *count1);
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
            printf("\nKey found at Index: %d", mid);
            printf("\nBinarySearch Comparisons: %d\n", *count2);
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

int main() {
    int count1 = 0, count2 = 0;
    int n;
    printf("Enter Size of Array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter Array Elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min = 0, high = n - 1;
    int x;
    printf("Enter value of key: ");
    scanf("%d", &x);

    int Ternary = TernarySearch(arr, min, high, x, &count1);
    if (Ternary == -1)
        printf("\nKey not found in Ternary Search\n");

    int Binary = BinarySearch(arr, min, high, x, &count2);
    if (Binary == -1)
        printf("\nKey not found in Binary Search\n");

    return 0;
}
