#include <stdio.h>
#include <string.h>

#define MAX 100

// Function to print LCS
void printLCS(char X[], char Y[], int m, int n, int L[MAX][MAX]) {
    if(m == 0 || n == 0)
        return;

    if(X[m-1] == Y[n-1]) {
        printLCS(X, Y, m-1, n-1, L);
        printf("%c", X[m-1]);
    }
    else if(L[m-1][n] > L[m][n-1])
        printLCS(X, Y, m-1, n, L);
    else
        printLCS(X, Y, m, n-1, L);
}

int main() {
    char X[MAX], Y[MAX];
    int L[MAX][MAX];
    
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);
    
    int m = strlen(X);
    int n = strlen(Y);

    // DP table fill
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == 0 || j == 0)
                L[i][j] = 0;
            else if(X[i-1] == Y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = (L[i-1][j] > L[i][j-1]) ? L[i-1][j] : L[i][j-1];
        }
    }

    printf("\nLength of LCS = %d\n", L[m][n]);
    printf("LCS = ");
    printLCS(X, Y, m, n, L);
    printf("\n");

    return 0;
}
