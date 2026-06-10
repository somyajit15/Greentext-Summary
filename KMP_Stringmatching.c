#include <stdio.h>
#include <string.h>

// Build LPS array
void buildLPS(char pat[], int m, int lps[]) {
    int len = 0, i = 1;
    lps[0] = 0;

    while(i < m) {
        if(pat[i] == pat[len])
            lps[i++] = ++len;
        else {
            if(len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
}

void KMP(char text[], char pat[]) {
    int n = strlen(text);
    int m = strlen(pat);
    int lps[m];

    buildLPS(pat, m, lps);

    int i = 0, j = 0;
    while(i < n) {

        if(text[i] == pat[j]) {
            i++; j++;
        }
        if(j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if(i < n && text[i] != pat[j]) {
            if(j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[100], pattern[50];

    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pattern);

    KMP(text, pattern);

    return 0;
}
