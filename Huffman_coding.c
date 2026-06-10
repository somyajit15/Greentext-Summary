#include <stdio.h>
#include <stdlib.h>

#define MAX 50   // Maximum number of characters supported

// -------------------------------
// Node structure for Huffman Tree
// -------------------------------
typedef struct Node {
    char ch;                // Character
    int freq;               // Frequency
    struct Node *left;      // Left child
    struct Node *right;     // Right child
} Node;


// ---------------------------------
// Create new node
// ---------------------------------
Node* createNode(char ch, int freq) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->ch = ch;
    n->freq = freq;
    n->left = n->right = NULL;
    return n;
}


// ------------------------------------------------------------
// Remove node with minimum frequency from array (min-heap-like)
// ------------------------------------------------------------
Node* removeMin(Node* heap[], int *size) {

    // Minimum node is at index 0
    Node* min = heap[0];

    // Replace first element with last
    heap[0] = heap[--(*size)];

    // Sort remaining heap again (simple bubble sort)
    for(int i = 0; i < *size; i++) {
        for(int j = i + 1; j < *size; j++) {
            if(heap[i]->freq > heap[j]->freq) {
                Node* tmp = heap[i];
                heap[i] = heap[j];
                heap[j] = tmp;
            }
        }
    }

    return min;
}


// ------------------------------------------------------------
// Print Huffman Codes by traversing the tree
// arr[] stores code bits
// top: index for next bit
// ------------------------------------------------------------
void printCodes(Node* root, int arr[], int top) {

    // Go left → assign 0
    if(root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Go right → assign 1
    if(root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // Leaf node → print character + code
    if(!root->left && !root->right) {
        printf("%c : ", root->ch);
        for(int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}


// -----------------------------------------
// MAIN
// -----------------------------------------
int main() {

    int n;
    Node* heap[MAX];

    printf("Enter number of characters: ");
    scanf("%d", &n);

    printf("\nEnter character and its frequency (ex: a 5):\n");

    for(int i = 0; i < n; i++) {
        char c;
        int f;
        scanf(" %c %d", &c, &f);
        heap[i] = createNode(c, f);
    }

    // Current heap size
    int size = n;

    // -----------------------------------------------------
    // Build Huffman Tree
    // -----------------------------------------------------
    while(size > 1) {

        // Remove two min freq nodes
        Node* left = removeMin(heap, &size);
        Node* right = removeMin(heap, &size);

        // Create new internal node
        Node* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Add new node back into heap
        heap[size++] = newNode;

        // Re-sort heap
        for(int i = 0; i < size; i++) {
            for(int j = i + 1; j < size; j++) {
                if(heap[i]->freq > heap[j]->freq) {
                    Node* t = heap[i];
                    heap[i] = heap[j];
                    heap[j] = t;
                }
            }
        }
    }

    // Huffman Tree root is now heap[0]

    int code[50];
    printf("\nHuffman Codes:\n");
    printCodes(heap[0], code, 0);

    return 0;
}
