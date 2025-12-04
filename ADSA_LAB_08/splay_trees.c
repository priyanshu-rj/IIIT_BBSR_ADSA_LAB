#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

/* ---------------- ROTATIONS ---------------- */

struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

/* ---------------- SPLAY OPERATION ---------------- */

struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        if (root->left == NULL)
            return root;

        // Zig-Zig (LL)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (LR)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }

    else {
        if (root->right == NULL)
            return root;

        // Zig-Zig (RR)
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        // Zig-Zag (RL)
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

/* ---------------- INSERT ---------------- */

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    struct Node* node = newNode(key);

    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = NULL;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = NULL;
    }
    return node;
}

/* ---------------- DELETE ---------------- */

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    root = splay(root, key);

    if (root->key != key)
        return root;  // key not found

    struct Node* temp;

    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

/* ---------------- INORDER TRAVERSAL ---------------- */

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

/* ---------------- MENU MAIN PROGRAM ---------------- */

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n===== SPLAY TREE MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search (Splay)\n");
        printf("4. Display (In-order)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            printf("Inserted and splayed to root.\n");
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("Deleted (if existed).\n");
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &key);
            root = splay(root, key);
            printf("After search, root = %d\n", root->key);
            break;

        case 4:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid option!\n");
        }
    }
    return 0;
}