#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void add(int A[10][10], int B[10][10], int C[10][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtract(int A[10][10], int B[10][10], int C[10][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen’s Algorithm for Matrix Multiplication
void strassen(int A[10][10], int B[10][10], int C[10][10], int n) {
    if (n == 1) {  // Base case
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int a11[10][10], a12[10][10], a21[10][10], a22[10][10];
    int b11[10][10], b12[10][10], b21[10][10], b22[10][10];
    int c11[10][10], c12[10][10], c21[10][10], c22[10][10];
    int p1[10][10], p2[10][10], p3[10][10], p4[10][10], p5[10][10], p6[10][10], p7[10][10];
    int temp1[10][10], temp2[10][10];

    // Divide matrices into 4 parts
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute the 7 products (Strassen formula)
    add(a11, a22, temp1, newSize);   // (A11 + A22)
    add(b11, b22, temp2, newSize);   // (B11 + B22)
    strassen(temp1, temp2, p1, newSize);  // P1 = (A11 + A22) * (B11 + B22)

    add(a21, a22, temp1, newSize);   // (A21 + A22)
    strassen(temp1, b11, p2, newSize);    // P2 = (A21 + A22) * B11

    subtract(b12, b22, temp2, newSize);   // (B12 - B22)
    strassen(a11, temp2, p3, newSize);    // P3 = A11 * (B12 - B22)

    subtract(b21, b11, temp2, newSize);   // (B21 - B11)
    strassen(a22, temp2, p4, newSize);    // P4 = A22 * (B21 - B11)

    add(a11, a12, temp1, newSize);        // (A11 + A12)
    strassen(temp1, b22, p5, newSize);    // P5 = (A11 + A12) * B22

    subtract(a21, a11, temp1, newSize);   // (A21 - A11)
    add(b11, b12, temp2, newSize);        // (B11 + B12)
    strassen(temp1, temp2, p6, newSize);  // P6 = (A21 - A11) * (B11 + B12)

    subtract(a12, a22, temp1, newSize);   // (A12 - A22)
    add(b21, b22, temp2, newSize);        // (B21 + B22)
    strassen(temp1, temp2, p7, newSize);  // P7 = (A12 - A22) * (B21 + B22)

    // Compute final quadrants of result matrix C
    add(p1, p4, temp1, newSize);
    subtract(temp1, p5, temp2, newSize);
    add(temp2, p7, c11, newSize);   // C11 = P1 + P4 - P5 + P7

    add(p3, p5, c12, newSize);      // C12 = P3 + P5

    add(p2, p4, c21, newSize);      // C21 = P2 + P4

    subtract(p1, p2, temp1, newSize);
    add(temp1, p3, temp2, newSize);
    add(temp2, p6, c22, newSize);   // C22 = P1 - P2 + P3 + P6

    // Combine all quadrants into final result matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }
}

int main() {
    int A[10][10], B[10][10], C[10][10];
    int n;

    printf("Enter size of square matrix (power of 2): ");
    scanf("%d", &n);

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(A, B, C, n);

    printf("\nResultant Matrix (A x B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
