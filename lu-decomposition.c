#include <stdio.h>

#define N 4   // Here it is taken as 3, it can be changed

// function to perform LU decomposition
void lu_decomposition(double A[N][N], double L[N][N], double U[N][N]) {
    for (int i = 0; i < N; i++) {

        // upper triangular matrix (U)
        for (int k = i; k < N; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }

        // lower triangular matrix (L)
        for (int k = i; k < N; k++) {
            if (i == k) {
                L[i][i] = 1; // Diagonal as 1
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

// Function to print a matrix
void printmatrix(double M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.3f ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    double A[N][N], L[N][N] = {0}, U[N][N] = {0};

    // insert the elements of the matrix
    printf("Enter the elements of a %dx%d matrix A:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nOriginal Matrix A:\n");
    printmatrix(A);

    // Perform LU Decomposition
    lu_decomposition(A, L, U);

    printf("\nLower Triangular Matrix L: \n"); // prints lower triangular matrix
    printmatrix(L);

    printf("\nUpper Triangular Matrix U: \n"); // print upper triangular matrix
    printmatrix(U);

    return 0;
}
