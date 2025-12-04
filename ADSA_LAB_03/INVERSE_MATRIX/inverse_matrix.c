#include <stdio.h>

#define MAX 10  

void printMatrix(double mat[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.3lf ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    double mat[MAX][MAX], inverse[MAX][MAX];

    printf("Enter size of square matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter elements of matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &mat[i][j]);


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inverse[i][j] = (i == j) ? 1 : 0;

    
    for (int i = 0; i < n; i++) {
        // Find pivot
        if (mat[i][i] == 0) {
            int swapRow = -1;
            for (int k = i+1; k < n; k++) {
                if (mat[k][i] != 0) {
                    swapRow = k;
                    break;
                }
            }
            if (swapRow == -1) {
                printf("Matrix is singular, cannot find inverse.\n");
                return 0;
            }
            // Swap rows
            for (int j = 0; j < n; j++) {
                double temp = mat[i][j];
                mat[i][j] = mat[swapRow][j];
                mat[swapRow][j] = temp;

                temp = inverse[i][j];
                inverse[i][j] = inverse[swapRow][j];
                inverse[swapRow][j] = temp;
            }
        }

        // Make pivot = 1
        double pivot = mat[i][i];
        for (int j = 0; j < n; j++) {
            mat[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = mat[k][i];
                for (int j = 0; j < n; j++) {
                    mat[k][j] -= factor * mat[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }

    printf("Inverse Matrix:\n");
    printMatrix(inverse, n);

    return 0;
}