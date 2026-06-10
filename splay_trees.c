
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Right Rotate
struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left Rotate
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay Operation
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        if (root->left == NULL)
            return root;

        if (key < root->left->key) { // Zig-Zig Left Left
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } 
        else if (key > root->left->key) { // Zig-Zag Left Right
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } 
    
    else {
        if (root->right == NULL)
            return root;

        if (key > root->right->key) { // Zag-Zag Right Right
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        } 
        else if (key < root->right->key) { // Zag-Zig Right Left
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert a key
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (key == root->key)
        return root;

    struct Node* node = newNode(key);

    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = NULL;
    } else {
        node->left = root;
        node->right = root->right;
        root->right = NULL;
    }

    return node;
}

// Search key and splay it
struct Node* search(struct Node* root, int key) {
    return splay(root, key);
}

// Delete a node
struct Node* delete(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    root = splay(root, key);

    if (key != root->key)
        return root;

    struct Node* temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
    return root;
}

// Preorder Traversal
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n\n--- SPLAY TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Preorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Inserted & Splayed.\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &key);
                root = search(root, key);
                printf("Search Complete. (If found, splayed to root)\n");
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                printf("Deleted (if existed).\n");
                break;

            case 4:
                printf("Preorder Traversal: ");
                preOrder(root);
                printf("\n");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
