 #include <stdio.h>


void heapify(int arr[], int n, int i) {      // function for heapify
    int largest = i;       
    int left = 2 * i + 1;     
    int right = 2 * i + 2;    
    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {        // fucntin for heapsort
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}
void printarr(int arr[], int n){     // fucntion to print the unsorted elements in the array
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
        }
    printf("\n");
}


int main() {
    int n;

    printf("Enter number of elements: "); // number of elements to be taken
    scanf("%d", &n);

    int arr[n];                          // elements stored in array
    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
 
    printf("Array before sorting: ");      // printing elements before sorting
    printarr(arr, n);

    heapSort(arr, n);                    // elements sorted using heap sort

    printf("sorted array: ");             // printing sorted array
    printarr(arr, n);


    return 0;    
}
