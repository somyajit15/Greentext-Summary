#include <stdio.h>


int binarysearch(int arr[], int left, int right, int target){ //binary search function using recursion
    if(left > right){
        return -1; //element is not present
    }

    int mid =  left + (right -left) /2;

    if(arr[mid]== target)
        return mid; // element found

    else if(arr[mid] > target)
       return binarysearch(arr, left, mid - 1, target); //element is present in left side of array
    
    else 
        return binarysearch(arr, mid+1, right, target);   // element is present in right side of array
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
     printf("Enter the elements in the array in increasing order: ");
     for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
     }

     printf("The given array is: ");
     printarr(arr,n);

     int target;
     printf("Enter the element you want to find in the array: ");
     scanf("%d", &target);

     int result = binarysearch(arr, 0, n-1, target);

      if(result!=-1){
        printf("Element %d found at index %d \n", target, result);
     }
     else{
        printf("Element not found\n");
     }

    return 0;
}