#include <stdio.h>
#include <math.h>

#define N 2        // number of variables (x1, x2)
#define M 2        // number of constraints
#define MAX_ITER 1000

// ---------------------------------------------------------
// FUNCTION: Check which constraint is violated at point x
// Returns: index of violated constraint OR -1 if all satisfy
// ---------------------------------------------------------
int violated_constraint(double A[M][N], double b[M], double x[N]) {
    for(int i = 0; i < M; i++) {

        double sum = 0;

        // Compute A[i] * x
        for(int j = 0; j < N; j++)
            sum += A[i][j] * x[j];

        // If A[i]x > b[i] → constraint violated
        if(sum > b[i])
            return i;  
    }
    return -1;  // All constraints satisfied
}

int main() {

    // ---------------------------------------------------------
    // Constraints:
    // 1) x1 + x2 <= 5
    // 2) -x1 - 2x2 <= -4   (same as x1 + 2x2 >= 4)
    // ---------------------------------------------------------
    double A[M][N] = {
        { 1,  1},
        {-1, -2}
    };

    double b[M] = {5, -4};

    // ---------------------------------------------------------
    // INITIAL CENTER of ellipsoid (start point)
    // (0,0) is NOT feasible → algorithm will move away
    // ---------------------------------------------------------
    double x[N] = {0, 0};

    // ---------------------------------------------------------
    // INITIAL ELLIPSOID SHAPE MATRIX P
    // Acts like radius/shape of the ellipsoid
    // ---------------------------------------------------------
    double P[N][N] = {
        {4, 0},
        {0, 4}
    };

    printf("Starting Ellipsoid Method...\n");

    // ---------------------------------------------------------
    // MAIN LOOP
    // ---------------------------------------------------------
    for(int iter = 0; iter < MAX_ITER; iter++) {

        // Check if current point is feasible
        int k = violated_constraint(A, b, x);

        // If no violation → feasible point found!
        if(k == -1) {
            printf("Feasible point found: (%.4f, %.4f)\n", x[0], x[1]);
            return 0;
        }

        // ---------------------------------------------------------
        // Step 1: g = normalized gradient direction of violated constraint
        // g = A[k] / ||A[k]||
        // ---------------------------------------------------------
        double g[N];
        double norm = 0;

        for(int i = 0; i < N; i++) {
            g[i] = A[k][i];
            norm += g[i] * g[i];
        }
        norm = sqrt(norm);

        for(int i = 0; i < N; i++)
            g[i] /= norm;

        // ---------------------------------------------------------
        // Step 2: Compute P * g
        // ---------------------------------------------------------
        double Pg[N];
        for(int i = 0; i < N; i++) {
            Pg[i] = 0;
            for(int j = 0; j < N; j++)
                Pg[i] += P[i][j] * g[j];
        }

        // ---------------------------------------------------------
        // Step 3: Compute scalar g^T * P * g
        // ---------------------------------------------------------
        double gPg = 0;
        for(int i = 0; i < N; i++)
            gPg += g[i] * Pg[i];

        // ---------------------------------------------------------
        // Step 4: Update center x of ellipsoid
        // x = x - (P*g) / ((N+1)*sqrt(gPg))
        // Moves ellipsoid towards feasible region
        // ---------------------------------------------------------
        for(int i = 0; i < N; i++)
            x[i] -= (Pg[i] / (sqrt(gPg) * (N + 1)));

        // ---------------------------------------------------------
        // Step 5: Update ellipsoid shape matrix P
        // Shrinks ellipsoid based on violated constraint
        // ---------------------------------------------------------
        double factor = (double)(N*N) / (N*N - 1);
        double temp[N][N];

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                temp[i][j] = P[i][j] -
                             (2.0 / ((N + 1) * gPg)) *
                             (Pg[i] * Pg[j]);

        // Apply factor to complete update
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                P[i][j] = factor * temp[i][j];

        // ---------------------------------------------------------
        // Print iteration details
        // ---------------------------------------------------------
        printf("Iteration %d: x = (%.4f, %.4f)\n", iter+1, x[0], x[1]);
    }

    printf("Max iterations reached. No feasible point found.\n");
    return 0;
}
