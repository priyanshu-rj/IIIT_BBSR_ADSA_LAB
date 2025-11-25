#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct Edge {
    char node1[20];
    char node2[20];
};

int main() {
    int n;
    printf("Enter number of interactions (edges): ");
    scanf("%d", &n);

    struct Edge edges[n];
    printf("Enter interactions in SIF format (e.g., A pp B):\n");

    for (int i = 0; i < n; i++) {
        char relation[10];
        scanf("%s %s %s", edges[i].node1, relation, edges[i].node2);
    }

    printf("\nGraph (Adjacency List Representation):\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> %s\n", edges[i].node1, edges[i].node2);
    }

    return 0;
}
