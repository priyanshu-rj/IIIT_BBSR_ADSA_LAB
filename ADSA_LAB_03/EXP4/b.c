#include <stdio.h>
#include <stdlib.h>

#define t 3  // Minimum degree (defines range for number of keys)

// Structure of a B-Tree node
struct BTreeNode {
    int keys[2*t - 1];
    struct BTreeNode *children[2*t];
    int n;           // Current number of keys
    int leaf;        // Is true when node is leaf
};

// Create a new B-Tree node
struct BTreeNode* createNode(int leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->leaf = leaf;
    newNode->n = 0;
    return newNode;
}

// Traverse
void traverse(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

// Search key
struct BTreeNode* search(struct BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == k)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->children[i], k);
}

// Split child
void splitChild(struct BTreeNode* parent, int i, struct BTreeNode* y) {
    struct BTreeNode* z = createNode(y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[t - 1];
    parent->n++;
}

// Insert non-full
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->children[i]->n == 2*t - 1) {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

// Insert into B-Tree
struct BTreeNode* insert(struct BTreeNode* root, int k) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }
    if (root->n == 2*t - 1) {
        struct BTreeNode* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (k > s->keys[0])
            i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

int main() {
    struct BTreeNode* root = NULL;

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++)
        root = insert(root, keys[i]);

    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    return 0;
}
