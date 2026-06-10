#include <stdio.h>

// merge two subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray
    
    int L[n1], R[n2];
    
    // copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    // merge the temp arrays back into arr[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    
    // copy the remaining elements
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// merge Sort recursive function
void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergesort(arr, left, mid);      // sort first half
        mergesort(arr, mid + 1, right); // sort second half
        merge(arr, left, mid, right);   // merge the sorted halves
    }
}

void printarr(int arr[], int n){     // fucntion to print the unsorted elements in the array
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
        }
    printf("\n");
}

int main(){
     int n;
     printf("Enter the number of elements to be inserted in array: ");
     scanf("%d", &n);


     int arr[n];
     printf("Enter the elements in the array to be sorted: ");
     for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
     }

     printf("The original given array is: ");
     printarr(arr,n);

    mergesort(arr, 0, n-1);

     printf("Sorted array using Merge sort is: ");
     printarr(arr,n);    




    return 0;
}