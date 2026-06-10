#include <stdio.h>
#include <math.h>

// Step 1: define barrier function
double barrier_function(double x, double y, double mu) {
    // objective: maximize x + y → minimize -(x + y)
    // barrier terms: -mu * (log(x) + log(y) + log(4 - x - y))
    return -(x + y) - mu * (log(x) + log(y) + log(4 - x - y));
}

// Step 2: gradient of barrier function
void gradient(double x, double y, double mu, double *gx, double *gy) {
    *gx = -1 - mu * (1/x - 1/(4 - x - y));
    *gy = -1 - mu * (1/y - 1/(4 - x - y));
}

// Step 3: iterative gradient descent
void interior_point_method() {
    double x = 1.0, y = 1.0;     // starting interior feasible point
    double mu = 1.0;             // initial barrier weight
    double step = 0.01;          // learning rate
    double gx, gy;

    for (int k = 0; k < 100; k++) {  // outer loop: decrease mu
        for (int i = 0; i < 500; i++) { // inner loop: optimization
            gradient(x, y, mu, &gx, &gy);

            // update x and y
            x = x - step * gx;
            y = y - step * gy;

            // keep x,y strictly positive
            if (x <= 0) x = 0.1;
            if (y <= 0) y = 0.1;
            if (x + y >= 4) { 
                double diff = (x + y) - 3.9;
                x -= diff/2;
                y -= diff/2;
            }
        }
        mu *= 0.5;  // shrink barrier
    }

    printf("Optimal solution:\n");
    printf("x = %.4f, y = %.4f\n", x, y);
    printf("Maximized value = %.4f\n", x + y);
}

int main() {
    interior_point_method();
    return 0;
}
