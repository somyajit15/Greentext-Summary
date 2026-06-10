#include <stdio.h>
#include <math.h>

#define N 3   // matrix size (change as needed)

// function to perform LU decomposition with partial pivoting
int lupDecomposition(double A[N][N], double L[N][N], double U[N][N], int P[N]) {
    for (int i = 0; i < N; i++) {
        P[i] = i;   // initialize permutation as identity
    }

    for (int i = 0; i < N; i++) {
        // pivot: find row with max element in column i
        double maxA = 0.0;
        int imax = i;
        for (int k = i; k < N; k++) {
            if (fabs(A[k][i]) > maxA) {
                maxA = fabs(A[k][i]);
                imax = k;
            }
        }

        // Singular matrix?
        if (maxA < 1e-12) return 0;  

        // Swap rows in A and P
        if (imax != i) {
            for (int j = 0; j < N; j++) {
                double tmp = A[i][j];
                A[i][j] = A[imax][j];
                A[imax][j] = tmp;
            }
            int tmpP = P[i];
            P[i] = P[imax];
            P[imax] = tmpP;
        }

        // Decompose
        for (int j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];
            for (int k = i + 1; k < N; k++) {
                A[j][k] -= A[j][i] * A[i][k];
            }
        }
    }

    // Extract L and U from modified A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > j) {
                L[i][j] = A[i][j];
                U[i][j] = 0;
            } else if (i == j) {
                L[i][j] = 1;
                U[i][j] = A[i][j];
            } else {
                L[i][j] = 0;
                U[i][j] = A[i][j];
            }
        }
    }
    return 1;
}

// Forward substitution for L*y = Pb
void forwardSubstitution(double L[N][N], double b[N], double y[N]) {
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }
}

// Backward substitution for U*x = y
void backwardSubstitution(double U[N][N], double y[N], double x[N]) {
    for (int i = N - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < N; j++) sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }
}

int main() {
    // Example system A*x = b
    double A[N][N] = {
        {0, 2, 1},
        {1, -2, -3},
        {2, 3, 1}
    };

    double b[N] = {3, -3, 4};

    double L[N][N] = {0}, U[N][N] = {0};
    int P[N];
    double x[N], y[N];

    if (!lupDecomposition(A, L, U, P)) {
        printf("Matrix is singular!\n");
        return -1;
    }

    // Apply permutation P to b → Pb
    double Pb[N];
    for (int i = 0; i < N; i++) {
        Pb[i] = b[P[i]];
    }

    // Solve Ly = Pb
    forwardSubstitution(L, Pb, y);

    // Solve Ux = y
    backwardSubstitution(U, y, x);

    printf("Permutation P:\n");
    for (int i = 0; i < N; i++) printf("%d ", P[i]);
    printf("\n\nLower triangular L:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%8.3f ", L[i][j]);
        printf("\n");
    }
    printf("\nUpper triangular U:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%8.3f ", U[i][j]);
        printf("\n");
    }
    printf("\nSolution x:\n");
    for (int i = 0; i < N; i++) printf("x[%d] = %.3f\n", i, x[i]);

    return 0;
}
