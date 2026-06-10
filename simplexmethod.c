#include <stdio.h>

#define MAX 10   // max variables + slack
#define INF 1e9

// here printing tableau function
void printTableau(int m, int n, double A[MAX][MAX]) {
    printf("\nCurrent Simplex Tableau:\n");
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++)
            printf("%8.2lf ", A[i][j]);
        printf("\n");
    }
}

// function of simplex Algorithm
void simplex(int m, int n, double A[MAX][MAX]) {
    while (1) {
        int pivotCol = -1, pivotRow = -1;

        // step 1 → Find entering variable (most positive coefficient in objective row)
        double max = 0;
        for (int j = 0; j < n; j++) {
            if (A[m][j] > max) {
                max = A[m][j];
                pivotCol = j;
            }
        }

        // if no positive entry → optimal reached
        if (pivotCol == -1)
            break;

        // step 2 → choose leaving variable (minimum ratio test)
        double minRatio = INF;
        for (int i = 0; i < m; i++) {
            if (A[i][pivotCol] > 0) {
                double ratio = A[i][n] / A[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }

        if (pivotRow == -1) {
            printf("Unbounded solution!\n");
            return;
        }

        // Step 3 → Pivot
        double pivot = A[pivotRow][pivotCol];

        // Normalize pivot row
        for (int j = 0; j <= n; j++)
            A[pivotRow][j] /= pivot;

        // Make pivotCol zero in other rows
        for (int i = 0; i <= m; i++) {
            if (i != pivotRow) {
                double factor = A[i][pivotCol];
                for (int j = 0; j <= n; j++)
                    A[i][j] -= factor * A[pivotRow][j];
            }
        }

        printTableau(m, n, A);   // display progress
    }

    printf("\nOptimal value: %.2lf\n", A[m][n]);
}

int main() {
    int m, n;

    // m = constraints,  n = variables
    printf("Enter number of constraints: ");
    scanf("%d", &m);
    printf("Enter number of variables: ");
    scanf("%d", &n);

    // Tableau size will be (m+1) x (n + m + 1)
    int cols = n + m;     // original + slack
    double A[MAX][MAX] = {0};

    printf("\nEnter coefficients of constraints (<= type):\n");
    for (int i = 0; i < m; i++) {
        printf("Constraint %d (a1 a2 ... an b): ", i+1);
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

        scanf("%lf", &A[i][cols]);  // RHS (b_i)

        A[i][n + i] = 1; // slack variable
    }

    printf("\nEnter coefficients of objective function:\nMax Z = c1*x1 + ...\n");
    for (int j = 0; j < n; j++)
        scanf("%lf", &A[m][j]);

    // Objective RHS = 0
    A[m][cols] = 0;

    printTableau(m, cols, A);
    simplex(m, cols, A);

    return 0;
}
