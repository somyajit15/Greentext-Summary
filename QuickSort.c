#include <stdio.h>

void swap(int* a, int* b ){
   int temp = *a;
   *a = *b;
   *b = temp;
}

//partion function

int partition(int arr[], int left, int right){
    int pivot = arr[right];

    int i = left-1;

    for(int j = left; j < right; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[right]);

    return i+1;

}


void quicksort(int arr[], int left, int right){
  if(left < right){
    int parindex =  partition(arr, left, right);

    quicksort(arr, left, parindex -1);
    quicksort(arr, parindex +1, right);
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

    quicksort(arr, 0, n-1);

     printf("Sorted array using Quick sort is: ");
     printarr(arr,n);    




    return 0;
}