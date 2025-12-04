
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ---------------- NODE STRUCTURE ---------------- */
typedef struct FibNode {
    int key, degree, mark;
    struct FibNode *parent, *child, *left, *right;
} FibNode;

/* ---------------- HEAP STRUCTURE ---------------- */
typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

/* ---------------- CREATE NODE ---------------- */
FibNode* createNode(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node->right = node;
    return node;
}

/* ---------------- CREATE HEAP ---------------- */
FibHeap* createHeap() {
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));
    H->min = NULL;
    H->n = 0;
    return H;
}

/* ------------ INSERT: ADD TO ROOT LIST ------------- */
void fibHeapInsert(FibHeap *H, FibNode *x) {
    if (H->min == NULL) {
        H->min = x;
    } else {
        x->right = H->min->right;
        x->left = H->min;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n++;
}

/* ------------ FIB HEAP LINK (CHILD ATTACH) ---------- */
void fibHeapLink(FibHeap *H, FibNode *y, FibNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    y->left = y->right = y;

    if (x->child == NULL)
        x->child = y;
    else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

/* ---------------- CONSOLIDATE --------------------- */
void consolidate(FibHeap *H) {
    int D = 50;
    FibNode *A[D];

    for (int i = 0; i < D; i++)
        A[i] = NULL;

    FibNode *w = H->min;
    if (!w) return;

    int count = 0;
    FibNode *curr = w;
    do { count++; curr = curr->right; } while (curr != w);

    while (count--) {
        FibNode *x = w;
        int d = x->degree;
        w = w->right;

        while (A[d]) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *tmp = x; x = y; y = tmp;
            }
            fibHeapLink(H, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    H->min = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i]) {
            if (!H->min) {
                /* IMPORTANT FIX: initialize single-node circular list */
                A[i]->left = A[i]->right = A[i];
                H->min = A[i];
            } else {
                A[i]->right = H->min->right;
                A[i]->left = H->min;
                H->min->right->left = A[i];
                H->min->right = A[i];
                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }
}

/* ---------------- EXTRACT MIN --------------------- */
FibNode* fibHeapExtractMin(FibHeap *H) {
    FibNode *z = H->min;
    if (z) {
        if (z->child) {
            FibNode *c = z->child;
            do {
                FibNode *next = c->right;
                c->parent = NULL;

                c->right = H->min->right;
                c->left = H->min;
                H->min->right->left = c;
                H->min->right = c;

                c = next;
            } while (c != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right)
            H->min = NULL;
        else {
            H->min = z->right;
            consolidate(H);
        }

        H->n--;
    }

    return z;
}

/* ---------------- CUT & CASCADING CUT ------------- */
void cut(FibHeap *H, FibNode *x, FibNode *y) {
    if (x->right == x)
        y->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }

    y->degree--;
    x->parent = NULL;
    x->left = x->right = x;
    x->mark = 0;

    x->right = H->min->right;
    x->left = H->min;
    H->min->right->left = x;
    H->min->right = x;
}

void cascadingCut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z) {
        if (!y->mark)
            y->mark = 1;
        else {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}

/* ---------------- DECREASE KEY --------------------- */
void fibHeapDecreaseKey(FibHeap *H, FibNode *x, int k) {
    if (k > x->key) {
        printf("New key greater—Invalid!\n");
        return;
    }

    x->key = k;
    FibNode *y = x->parent;

    if (y && x->key < y->key) {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}

/* ---------------- DELETE NODE --------------------- */
void fibHeapDelete(FibHeap *H, FibNode *x) {
    fibHeapDecreaseKey(H, x, INT_MIN);
    FibNode *m = fibHeapExtractMin(H);
    free(m);
}

/* ---------------- DISPLAY ROOT LIST --------------- */
void display(FibHeap *H) {
    if (!H->min) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Root List: ");
    FibNode *curr = H->min;
    do {
        printf("%d ", curr->key);
        curr = curr->right;
    } while (curr != H->min);

    printf("\n");
}

/* ---------------- MAIN MENU ----------------------- */
int main() {
    FibHeap *H = createHeap();
    FibNode *nodes[1000];   // store node pointers
    int value, old, newk, choice, idx = 0;

    while (1) {
        printf("\n===== FIBONACCI HEAP MENU =====\n");
        printf("1. Insert\n");
        printf("2. Get Min\n");
        printf("3. Extract Min\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Display Root List\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            nodes[idx] = createNode(value);
            fibHeapInsert(H, nodes[idx]);
            idx++;
            break;

        case 2:
            if (H->min)
                printf("Minimum = %d\n", H->min->key);
            else
                printf("Heap empty.\n");
            break;

        case 3: {
            FibNode *m = fibHeapExtractMin(H);
            if (m) {
                printf("Extracted Min = %d\n", m->key);
                free(m);
            } else printf("Heap empty.\n");
            break;
        }

        case 4:
            printf("Enter existing key: ");
            scanf("%d", &old);
            printf("Enter new (smaller) key: ");
            scanf("%d", &newk);
            for (int i = 0; i < idx; i++)
                if (nodes[i] && nodes[i]->key == old)
                    fibHeapDecreaseKey(H, nodes[i], newk);
            break;

        case 5:
            printf("Enter key to delete: ");
            scanf("%d", &value);
            for (int i = 0; i < idx; i++)
                if (nodes[i] && nodes[i]->key == value)
                    fibHeapDelete(H, nodes[i]);
            printf("Deleted.\n");
            break;

        case 6:
            display(H);
            break;

        case 7:
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
