// TERNARY SEARCH

#include <stdio.h>

int TernarySearch(int arr[], int min, int high,int x){
    
    while (min <= high) {
        int mid1 = min + (high - min) / 3;
        int mid2 = high - (high - min) / 3;

        if (arr[mid1] == x) {
            printf("Index Found at Index :");
            printf("%d",mid1);
            return 0;
        }
        
        else if(arr[mid2] == x) {
            printf("%d","Index Found at Index :");
            printf("%d",mid1);
            return 0;
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

int BinarySearch(int arr[], int min, int high,int x){
    
 while (min <= high) {
        int mid = min + (high - min) / 2;

        if (arr[mid] == x){
            printf("Key found at Index");
            printf("%d",mid);
            return 0;
        }
            

        if (arr[mid] < x){
            min = mid + 1;
        }
            
        else{
            high = mid - 1;
        }
            
    }
  return -1;
}


int main() {
    
    int n;
    printf("Enter Size of Array :");
    scanf("%d", &n);
    printf("Enter Array Elements :");
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
    int min = 0;
    int high = n - 1;
    printf("Enter value of key :");
    int x;
    scanf("%d",&x);
    
    int Ternary = TernarySearch(arr,min,high,x);
    int Binary = BinarySearch(arr,min,high,x);

    if(Ternary==-1){
       printf("Not found"); 
    }
    if(Binary==-1){
       printf("Not found"); 
    }
    
    return 0;
}