#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZE 12   // total number of functions

// Defining the functions

double f1(double n)  {                                      // Θ(n log n)
     return n * log2(n); 
    }                
double f2(double n)  {                                      // Θ(√n)
     return 12 * sqrt(n); 
    }               
double f3(double n)  {                                      // Θ(1/n)
     return 1.0 / n; 
    }                    
double f4(double n)  {                                      // Super-polynomial
     return pow(n, log2(n)); 
    }            
double f5(double n)  {                                      // Θ(n^2)
     return 100*pow(n,2) + 6*n; 
    }         
double f6(double n)  {                                      // Θ(n^0.51)
     return pow(n, 0.51); 
    }               
double f7(double n)  {                                      // Θ(n^2)
     return pow(n,2) - 324; 
    }             
double f8(double n)  {                                      // Θ(√n)
     return 50 * sqrt(n); 
    }               
double f9(double n)  {                                      // Θ(n^3)
     return 2 * pow(n,3); 
    }              
double f10(double n) {                                      // Θ(3^n)
     return pow(3,n); 
    }                   
double f11(double n) {                                      // Θ(n)
     return pow(2,32) * n; 
    }              
double f12(double n) {                                      // Θ(log n)
     return log2(n); 
    }      
    
    

int main() {
    double n;
    printf("Enter a value of n: ");
    scanf("%lf", &n);

    // Arrays to store names and values
    char *names[SIZE] = {
        "n log2(n)",
        "12 sqrt(n)",
        "1/n",
        "n^(log2 n)",
        "100n^2 + 6n",
        "n^0.51",
        "n^2 - 324",
        "50 sqrt(n)",
        "2n^3",
        "3^n",
        "(2^32)*n",
        "log2(n)"
    };

    double values[SIZE] = {
        f1(n), f2(n), f3(n), f4(n), f5(n), f6(n),
        f7(n), f8(n), f9(n), f10(n), f11(n), f12(n)
    };

    // sorting the values 
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (values[i] > values[j]) {
                // swap values
                double tempVal = values[i];
                values[i] = values[j];
                values[j] = tempVal;

                // swap corresponding names
                char *tempName = names[i];
                names[i] = names[j];
                names[j] = tempName;
            }
        }
    }

    // Printing  results in increasing order or growth
    printf("\nFunctions in increasing order of growth (at n = %.0f):\n\n", n);
    for (int i = 0; i < SIZE; i++) {

        printf("%-15s : %.6e\n", names[i], values[i]);
    }

    
    // Check Θ-equivalent pairs using ratio at two different n values
    
    double n1 = 1000, n2 = 10000;
    double (*funcs[SIZE])(double) = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12};

    printf("\nChecking Θ-equivalent pairs using ratio test at n=%.0f and n=%.0f:\n\n", n1, n2);

    for (int i = 0; i < SIZE; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            double r1 = funcs[i](n1) / funcs[j](n1);
            double r2 = funcs[i](n2) / funcs[j](n2);

            // If ratios are finite and close, consider them Θ-equivalent
            if (r1 > 0.0001 && r2 > 0.0001 && fabs(r1/r2 - 1) < 0.1) {
                printf("%-15s ~ %-15s  (ratios: %.3f , %.3f)\n", names[i], names[j], r1, r2);
            }
        }
    }

    return 0;
}
