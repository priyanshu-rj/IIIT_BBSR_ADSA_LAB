#include <stdio.h>
#include <math.h>

// Functions
double f1(int n) { return 1.0 / n; }
double f2(int n) { return log2(n); }
double f3(int n) { return 12 * sqrt(n); }
double f4(int n) { return 50 * sqrt(n); }
double f5(int n) { return pow(n, 0.51); }
double f6(int n) { return n * log2(n); }
double f7(int n) { return 100.0 * n * n + 6 * n; }
double f8(int n) { return (double)n * n - 324; }
double f9(int n) { return 2.0 * pow(n, 3); }
double f10(int n) { return pow(n, log2(n)); }
double f11(int n) { return pow(3, n); }
double f12(int n) { return pow(2, 3*n); }

int main() {
    char *names[12] = {
        "1/n", "log2(n)", "12*sqrt(n)", "50*sqrt(n)", "n^0.51", "n*log(n)",
        "100n^2+6n", "n^2-324", "2n^3", "n^log(n)", "3^n", "2^(3n)"
    };

    double sums[12] = {0};   // to store total sums
    int count = 0;           // number of n values

    // Step 1: compute sum for each function over n
    for (int n = 2; n <= 128; n += 2) {
        double values[12] = {
            f1(n), f2(n), f3(n), f4(n), f5(n), f6(n),
            f7(n), f8(n), f9(n), f10(n), f11(n), f12(n)
        };

        for (int i = 0; i < 12; i++) {
            sums[i] += values[i];
        }
        count++;
    }

    // Step 2: compute averages
    double avg[12];
    for (int i = 0; i < 12; i++) {
        avg[i] = sums[i] / count;
    }

    // Step 3: sort (bubble sort)
    for (int i = 0; i < 12; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (avg[i] > avg[j]) {
                double tmp = avg[i]; avg[i] = avg[j]; avg[j] = tmp;
                char *tmpName = names[i]; names[i] = names[j]; names[j] = tmpName;
            }
        }
    }

    // Step 4: print result
    printf("\nAverage Increasing Order of Functions (n = 2 to 128):\n");
    for (int i = 0; i < 12; i++) {
        printf("%s", names[i]);
        if (i < 11) printf(" < ");
    }
    printf("\n");

    return 0;
}