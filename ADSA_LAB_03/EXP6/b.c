#include <stdio.h>

#define MAX 100

int parent[MAX];

// Find set of an element i
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Perform union of two subsets
void union1(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void kruskalMST(int cost[MAX][MAX], int n) {
    int mincost = 0;
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int edges = 0;
    while (edges < n - 1) {
        int min = 999, a = -1, b = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (find(i) != find(j) && cost[i][j] < min && cost[i][j] != 0) {
                    min = cost[i][j];
                    a = i;
                    b = j;
                }

        union1(a, b);
        printf("Edge %d: (%d - %d) cost = %d\n", edges + 1, a, b, min);
        mincost += min;
        cost[a][b] = cost[b][a] = 999;
        edges++;
    }

    printf("\nMinimum cost = %d\n", mincost);
}

int main() {
    int n;
    int cost[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, n);
    return 0;
}
