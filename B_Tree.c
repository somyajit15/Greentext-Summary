#include <stdio.h>
#include <stdlib.h>
#define T 3  // Minimum degree

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode *child[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode *createNode(int leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    return node;
}

void traverse(BTreeNode *root) {
    int i;
    for(i=0;i<root->n;i++) {
        if(!root->leaf)
            traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->child[i]);
}

void splitChild(BTreeNode *x, int i) {
    BTreeNode *z = createNode(x->child[i]->leaf);
    BTreeNode *y = x->child[i];
    z->n = T - 1;

    for(int j=0; j < T-1; j++)
        z->keys[j] = y->keys[j+T];

    if(!y->leaf)
        for(int j=0; j < T; j++)
            z->child[j] = y->child[j+T];

    y->n = T - 1;

    for(int j=x->n; j >= i+1; j--)
        x->child[j+1] = x->child[j];

    x->child[i+1] = z;

    for(int j=x->n-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[T-1];
    x->n++;
}

void insertNonFull(BTreeNode *x, int k) {
    int i = x->n - 1;
    if(x->leaf) {
        while(i>=0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while(i>=0 && k < x->keys[i])
            i--;
        if(x->child[i+1]->n == 2*T-1) {
            splitChild(x, i+1);
            if(k > x->keys[i+1])
                i++;
        }
        insertNonFull(x->child[i+1], k);
    }
}

BTreeNode *insert(BTreeNode *root, int k) {
    if(root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }

    if(root->n == 2*T-1) {
        BTreeNode *s = createNode(0);
        s->child[0] = root;
        splitChild(s,0);

        int i = (k > s->keys[0]) ? 1 : 0;
        insertNonFull(s->child[i], k);
        return s;
    }
    insertNonFull(root,k);
    return root;
}

int main() {
    BTreeNode *root = NULL;
    int ch, val;

    while(1) {
        printf("\n1.Insert\n2.Display\n3.Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            root = insert(root,val);
            break;
        case 2:
            traverse(root);
            printf("\n");
            break;
        default:
            exit(0);
        }
    }
}
