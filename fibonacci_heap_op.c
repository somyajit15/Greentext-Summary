#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// =========================
//  Node & Heap Structures
// =========================

typedef struct Node {
    int key;
    int degree;
    int mark;
    struct Node* parent;
    struct Node* child;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct FibonacciHeap {
    Node* min;
    int n;
} FibonacciHeap;

// =========================
//  Create Node
// =========================

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

// =========================
//  Create Heap
// =========================

FibonacciHeap* createHeap() {
    FibonacciHeap* heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

static void insertNodeIntoRootList(FibonacciHeap* heap, Node* node) {
    if (heap->min == NULL) {
        heap->min = node;
        node->left = node->right = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
    }
}

// =========================
//  Insert Operation
// =========================

void insert(FibonacciHeap* heap, int key) {
    Node* node = createNode(key);
    insertNodeIntoRootList(heap, node);

    if (node->key < heap->min->key) {
        heap->min = node;
    }

    heap->n++;
}

// =========================
//  Find-Min
// =========================

Node* findMin(FibonacciHeap* heap) {
    return heap->min;
}

static void removeNodeFromList(Node* x) {
    x->left->right = x->right;
    x->right->left = x->left;
}

static void addChild(Node* parent, Node* child) {
    child->parent = parent;
    child->mark = 0;

    if (parent->child == NULL) {
        parent->child = child;
        child->left = child->right = child;
    } else {
        child->left = parent->child;
        child->right = parent->child->right;
        parent->child->right->left = child;
        parent->child->right = child;
    }

    parent->degree++;
}

static void linkTrees(Node* y, Node* x) {
    removeNodeFromList(y);
    addChild(x, y);
}

static void consolidate(FibonacciHeap* heap) {
    if (heap->min == NULL) return;

    int maxDegree = (int)(log2(heap->n)) + 2;
    Node** A = (Node**)calloc(maxDegree, sizeof(Node*));

    Node* start = heap->min;
    Node* w = start;
    int rootsCount = 0;
    do {
        rootsCount++;
        w = w->right;
    } while (w != start);

    w = start;
    for (int i = 0; i < rootsCount; ++i) {
        Node* x = w;
        w = w->right;
        int d = x->degree;

        while (A[d] != NULL) {
            Node* y = A[d];
            if (x->key > y->key) {
                Node* temp = x;
                x = y;
                y = temp;
            }
            linkTrees(y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    heap->min = NULL;

    for (int i = 0; i < maxDegree; ++i) {
        if (A[i] != NULL) {
            if (heap->min == NULL) {
                A[i]->left = A[i]->right = A[i];
                heap->min = A[i];
            } else {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                heap->min->right = A[i];

                if (A[i]->key < heap->min->key) {
                    heap->min = A[i];
                }
            }
        }
    }

    free(A);
}

// =========================
//  Extract-Min
// =========================

Node* extractMin(FibonacciHeap* heap) {
    Node* z = heap->min;

    if (z != NULL) {
        Node* child = z->child;
        if (child != NULL) {
            Node* start = child;
            Node* c = start;
            do {
                Node* next = c->right;
                c->left->right = c->right;
                c->right->left = c->left;
                c->parent = NULL;
                insertNodeIntoRootList(heap, c);
                c = next;
            } while (c != start);
        }

        z->child = NULL;

        if (z->right == z) {
            heap->min = NULL;
        } else {
            heap->min = z->right;
            removeNodeFromList(z);
            consolidate(heap);
        }

        heap->n--;
    }

    return z;
}

// =========================
//  Print Root List
// =========================

void printRootList(FibonacciHeap* heap) {
    if (heap->min == NULL) {
        printf("Heap is empty!\n");
        return;
    }

    Node* start = heap->min;
    Node* x = start;
    printf("Root list: ");
    do {
        printf("%d ", x->key);
        x = x->right;
    } while (x != start);
    printf("\n");
}

// =========================
//  MAIN (Menu Driven)
// =========================

int main() {
    FibonacciHeap* heap = createHeap();
    int choice, value;
    Node* minNode;
    
    while (1) {
        printf("\n======= Fibonacci Heap Menu =======\n");
        printf("1. Insert\n");
        printf("2. Find Minimum\n");
        printf("3. Extract Minimum\n");
        printf("4. Print Heap (Root List)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(heap, value);
            printf("Inserted!\n");
            break;

        case 2:
            minNode = findMin(heap);
            if (minNode)
                printf("Minimum = %d\n", minNode->key);
            else
                printf("Heap is empty!\n");
            break;

        case 3:
            minNode = extractMin(heap);
            if (minNode) {
                printf("Extracted Minimum = %d\n", minNode->key);
                free(minNode);
            } else {
                printf("Heap is empty!\n");
            }
            break;

        case 4:
            printRootList(heap);
            break;

        case 5:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
