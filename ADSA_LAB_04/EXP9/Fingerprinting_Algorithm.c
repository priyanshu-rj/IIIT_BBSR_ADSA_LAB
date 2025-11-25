#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256   // Number of characters in the input alphabet
#define q 101   // A prime number for Rabin-Karp hashing

// ------------------- KMP Algorithm ---------------------

// Function to compute LPS (Longest Prefix Suffix) array
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;   // lps[0] is always 0
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]

    printf("\nKMP Algorithm:\n");

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

// ------------------- Rabin-Karp Algorithm ---------------------

void RabinKarpSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0;  // hash value for text
    int h = 1;

    // The value of h would be pow(d, M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    printf("\nRabin-Karp Algorithm:\n");

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            int match = 1;
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    match = 0;
                    break;
                }
            }
            if (match)
                printf("Pattern found at index %d\n", i);
        }

        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}

// ------------------- Main Function ---------------------

int main() {
    char txt[100], pat[50];

    printf("Enter the text: ");
    gets(txt);
    printf("Enter the pattern: ");
    gets(pat);

    KMPSearch(pat, txt);
    RabinKarpSearch(pat, txt);

    return 0;
}
