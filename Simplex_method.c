#include <stdio.h>

#define ROWS 3   // 2 constraints + 1 Z-row
#define COLS 5   // x1, x2, s1, s2, RHS

void printTableau(float table[ROWS][COLS]) {
    printf("\n-------------------------------------------------\n");
    printf("   x1\t  x2\t  s1\t  s2\t  RHS\n");
    for (int i = 0; i < ROWS; i++) {
        if (i == ROWS - 1)
            printf("Z | ");
        else
            printf("R%d| ", i + 1);
        for (int j = 0; j < COLS; j++)
            printf("%6.2f\t", table[i][j]);
        printf("\n");
    }
    printf("-------------------------------------------------\n");
}

int main() {
    // Initial simplex tableau
    float table[ROWS][COLS] = {
        {1, 1, 1, 0, 4},   // x1 + x2 + s1 = 4
        {1, 3, 0, 1, 6},   // x1 + 3x2 + s2 = 6
        {-3, -2, 0, 0, 0}  // Z - 3x1 - 2x2 = 0
    };

    printf("Initial Simplex Tableau:\n");
    printTableau(table);

    while (1) {
        // Step 1: Identify entering variable (most negative in Z-row)
        int pivotCol = -1;
        float minVal = 0;
        for (int j = 0; j < COLS - 1; j++) {
            if (table[ROWS - 1][j] < minVal) {
                minVal = table[ROWS - 1][j];
                pivotCol = j;
            }
        }

        // If no negative coefficient in Z-row, optimal reached
        if (pivotCol == -1)
            break;

        // Step 2: Identify leaving variable (minimum ratio test)
        int pivotRow = -1;
        float minRatio = 1e9; // large number
        for (int i = 0; i < ROWS - 1; i++) {
            float colVal = table[i][pivotCol];
            if (colVal > 0) {
                float ratio = table[i][COLS - 1] / colVal;
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }

        if (pivotRow == -1) {
            printf("Unbounded solution detected!\n");
            return 0;
        }

        // Step 3: Pivot operation
        float pivot = table[pivotRow][pivotCol];
        // Normalize the pivot row
        for (int j = 0; j < COLS; j++)
            table[pivotRow][j] /= pivot;

        // Make other rows 0 in pivot column
        for (int i = 0; i < ROWS; i++) {
            if (i != pivotRow) {
                float factor = table[i][pivotCol];
                for (int j = 0; j < COLS; j++)
                    table[i][j] -= factor * table[pivotRow][j];
            }
        }

        printf("\nPivot on element at Row %d, Column %d (Value %.2f)\n",
               pivotRow + 1, pivotCol + 1, pivot);
        printTableau(table);
    }

    // Final results
    printf("\nOptimal Solution Reached!\n");
    printf("Final Tableau:\n");
    printTableau(table);

    float Z = table[ROWS - 1][COLS - 1];
    float x1 = 0, x2 = 0;

    // Read variable values (x1,x2,s1,s2) from tableau
    // If a column looks like a unit vector, the RHS value of that row is the variable value
    for (int j = 0; j < 2; j++) { // x1 and x2 columns
        int count1 = 0, pos = -1;
        for (int i = 0; i < ROWS - 1; i++) {
            if (table[i][j] == 1) { count1++; pos = i; }
            else if (table[i][j] != 0) { count1 = -1; break; }
        }
        if (count1 == 1 && pos != -1) {
            if (j == 0) x1 = table[pos][COLS - 1];
            else if (j == 1) x2 = table[pos][COLS - 1];
        }
    }

    printf("\nOptimal values:\n");
    printf("x1 = %.2f\n", x1);
    printf("x2 = %.2f\n", x2);
    printf("Z  = %.2f\n", Z);

    return 0;
}