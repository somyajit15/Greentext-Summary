#include <stdio.h>
#include <stdlib.h>

int comp_binary, comp_ternary;  // global counters

// binary search with comparison count
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        comp_binary++;   // one comparison
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) 
            return mid;
        else if (arr[mid] < key) 
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return -1; // not found
}

// ternary search with comparison count
int ternarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        comp_ternary++;
        if (arr[mid1] == key) 
            return mid1;

        comp_ternary++;
        if (arr[mid2] == key) 
            return mid2;

        if (key < arr[mid1]) 
            high = mid1 - 1;
        else if (key > arr[mid2]) 
            low = mid2 + 1;
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1; // not found
}

// function to print a bar of symbols
void printBar(int count, char symbol) {
    for (int i = 0; i < count; i++)
        printf("%c", symbol);
}

int main() {
    printf("Comparisons Table:\n");
    printf(" n\tBinary\tTernary\n");

    int sizes[] = {10, 100, 1000, 10000, 100000};           // test sizes
    int results[5][2];            // to store comparison counts

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));

        // initialize sorted array [1, 2, 3, ..., n]
        for (int j = 0; j < n; j++) 
            arr[j] = j + 1;

        int key = n;               // search for the last element (worst case)

        // reset counters
        comp_binary = comp_ternary = 0;

        binarySearch(arr, 0, n - 1, key);
        ternarySearch(arr, 0, n - 1, key);

        results[i][0] = comp_binary;
        results[i][1] = comp_ternary;

        printf("%d\t%d\t%d\n", n, comp_binary, comp_ternary);

        free(arr);
    }

    // Ascii graph
    printf("\nGraph ( * = Binary , # = Ternary )\n");
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        printf("n=%-7d | ", n);

        printBar(results[i][0], '*');
        printf("  ");
        printBar(results[i][1], '#');
        printf("\n");
    }

    return 0;
}
