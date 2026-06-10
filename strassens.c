#include <stdio.h>

#define MAX 2   // Works for 2x2 (simple lab version)

// Strassen multiplication for 2x2 matrix
void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {

    int a = A[0][0], b = A[0][1],
        c = A[1][0], d = A[1][1];

    int e = B[0][0], f = B[0][1],
        g = B[1][0], h = B[1][1];

    // Main formulas
    int p1 = a * (f - h);
    int p2 = (a + b) * h;
    int p3 = (c + d) * e;
    int p4 = d * (g - e);
    int p5 = (a + d) * (e + h);
    int p6 = (b - d) * (g + h);
    int p7 = (a - c) * (e + f);

    C[0][0] = p5 + p4 - p2 + p6;
    C[0][1] = p1 + p2;
    C[1][0] = p3 + p4;
    C[1][1] = p1 + p5 - p3 - p7;
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter Matrix A (2x2):\n");
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B (2x2):\n");
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d", &B[i][j]);

    strassen(A, B, C);

    printf("\nResult of A x B:\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}
