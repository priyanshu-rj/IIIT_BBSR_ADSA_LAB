#include <stdio.h>
#include <string.h>

// Function to compute Longest Prefix Suffix array
void computeLPS(char pat[], int m, int lps[]) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m) {
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

// KMP search function
void KMPsearch(char text[], char pat[]) {
    int n = strlen(text);
    int m = strlen(pat);

    int lps[m];
    computeLPS(pat, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    int found = 0; // flag to check match

    while (i < n) {
        if (pat[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            found = 1;
            j = lps[j - 1]; // continue searching
        }

        else if (i < n && pat[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found\n");
}

// Main function
int main() {
    char text[100], pattern[100];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // remove newline

    printf("Enter pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0;

    KMPsearch(text, pattern);

    return 0;
}