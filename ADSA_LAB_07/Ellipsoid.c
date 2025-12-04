#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 10     // Max dimension
#define MAXM 50     // Max constraints
#define EPS 1e-6    // Numerical tolerance
#define MAX_ITER 1000

// Matrix utilities
void print_vector(double *x, int n) {
    for(int i = 0; i < n; i++) printf("%.6f ", x[i]);
    printf("\n");
}

void mat_vec(double Q[MAXN][MAXN], double *v, double *out, int n) {
    for(int i = 0; i < n; i++) {
        out[i] = 0;
        for(int j = 0; j < n; j++) out[i] += Q[i][j] * v[j];
    }
}

double dot(double *a, double *b, int n) {
    double s = 0;
    for(int i = 0; i < n; i++) s += a[i] * b[i];
    return s;
}

// Ellipsoid Method
int ellipsoid(int m, int n, double A[MAXM][MAXN], double *b) {

    double x[MAXN] = {0};         // Center
    double Q[MAXN][MAXN];         // Shape matrix

    // Initialize as big sphere: Q = R^2 * I
    double R = 10.0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            Q[i][j] = (i == j) ? R*R : 0;

    double AQ[MAXN], direction[MAXN];

    for(int iter = 0; iter < MAX_ITER; iter++) {

        // Check all constraints
        int violated = -1;
        for(int i = 0; i < m; i++) {
            double s = dot(A[i], x, n);
            if(s > b[i] + EPS) { violated = i; break; }
        }

        if(violated == -1) {
            printf("Feasible point found in %d iterations:\n", iter);
            print_vector(x, n);
            return 1;
        }

        // Compute update for violated constraint
        int i = violated;

        mat_vec(Q, A[i], AQ, n);               // Q * a_i
        double denom = sqrt(dot(A[i], AQ, n)); // sqrt(a^T Q a)

        if(denom < EPS) {
            printf("Degenerate ellipsoid — cannot continue.\n");
            return 0;
        }

        // Update center x = x - (1/(n+1)) * (Q a_i)/sqrt(...)
        for(int k = 0; k < n; k++)
            direction[k] = AQ[k] / denom;

        for(int k = 0; k < n; k++)
            x[k] -= direction[k] / (n + 1);

        // Update Q
        double factor1 = (double)(n*n) / (n*n - 1);
        double factor2 = (double)2.0 / (n + 1);

        for(int r = 0; r < n; r++)
            for(int c = 0; c < n; c++)
                Q[r][c] = factor1 * (Q[r][c] - factor2 * (direction[r] * direction[c]));

    }

    printf("No feasible point found — iteration limit reached.\n");
    return 0;
}

// ----------------------- MAIN -----------------------

int main() {
    int m, n;
    double A[MAXM][MAXN], b[MAXM];

    printf("Enter number of constraints m: ");
    scanf("%d", &m);

    printf("Enter dimension n: ");
    scanf("%d", &n);

    printf("Enter matrix A (each row has n values):\n");
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Enter vector b (m values):\n");
    for(int i = 0; i < m; i++) scanf("%lf", &b[i]);

    ellipsoid(m, n, A, b);

    return 0;
}