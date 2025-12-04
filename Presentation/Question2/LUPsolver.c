#include <stdio.h>
#include <math.h>

#define N 3        // matrix size (change as needed)
#define EPS 1e-9   // tolerance for zero check

// Swap two rows in A and permutation array P
void swap_rows(double A[N][N], int P[N], int r1, int r2) {
    for (int j = 0; j < N; j++) {
        double tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    int t = P[r1]; P[r1] = P[r2]; P[r2] = t;
}

// LUP decomposition (A -> L and U in place, P is permutation)
int lup_decompose(double A[N][N], int P[N]) {
    for (int i = 0; i < N; i++) P[i] = i;

    for (int k = 0; k < N; k++) {
        // Pivot
        int pivot = k;
        double maxval = fabs(A[k][k]);
        for (int i = k + 1; i < N; i++) {
            if (fabs(A[i][k]) > maxval) {
                maxval = fabs(A[i][k]);
                pivot = i;
            }
        }
        if (maxval < EPS) return 0; // singular matrix

        if (pivot != k) swap_rows(A, P, k, pivot);

        // Elimination
        for (int i = k + 1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < N; j++)
                A[i][j] -= A[i][k] * A[k][j];
        }
    }
    return 1;
}

// Solve Ax = b using LUP result
void lup_solve(double A[N][N], int P[N], double b[N], double x[N]) {
    double y[N];

    // Forward substitution: Ly = Pb
    for (int i = 0; i < N; i++) {
        y[i] = b[P[i]];
        for (int j = 0; j < i; j++)
            y[i] -= A[i][j] * y[j];
    }

    // Backward substitution: Ux = y
    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}

int main() {
    double A[N][N], b[N], x[N];
    int P[N];

    // Take input for matrix A
    printf("Enter the elements of matrix A (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Take input for vector b
    printf("Enter the elements of vector b (%d values):\n", N);
    for (int i = 0; i < N; i++) {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
    }

    // Perform decomposition
    if (!lup_decompose(A, P)) {
        printf("Matrix is singular!\n");
        return 1;
    }

    // Solve system
    lup_solve(A, P, b, x);

    // Print solution
    printf("\nSolution x:\n");
    for (int i = 0; i < N; i++) {
        if (fabs(x[i]) < 1e-9) x[i] = 0; // avoid -0
        printf("x[%d] = %.6f\n", i, x[i]);
    }

    return 0;
}
