Function Growth Rate Comparison:

This program compares the growth of 12 mathematical functions related to algorithm complexity.
It sorts them for a given input n and checks Θ-equivalent pairs using ratio tests at n=1000 and n=10000.

--------------------------------------------------------------------------------------------------------

Functions Implemented: 

1) nlog2(n)

2) 12sqrt(n)

3) 1/n

4) n^(log2 n)

5) 100n² + 6n

6) n^0.51

7) n² - 324

8) 50sqrt(n)

9) 2n³

10) 3^n

11) (2^32) * n

12) log2(n)

--------------------------------------------------------------------------------------------------------

Eg -  Run (n = 50)

Functions in increasing order of growth:

1/n : 2.000000e-02
log2(n) : 5.643856e+00
n^0.51 : 7.049802e+00
12 sqrt(n) : 8.485281e+01
50 sqrt(n) : 3.535534e+02
n log2(n) : 2.821928e+02
(2^32)*n : 2.147484e+11
100n²+6n : 2.503000e+05
n²-324 : 2.147600e+03
2n³ : 2.500000e+05
n^(log2 n) : 8.881784e+84
3^n : 7.178980e+23
 
-------------------------------------------------------------------------------------------------------- 

Θ-equivalent pairs detected (n=1000 and n=10000):

12 sqrt(n) ~ 50 sqrt(n)
100n²+6n ~ n²-324

--------------------------------------------------------------------------------------------------------
What one can learn from this program:

Compare algorithm growth rates practically.
Understand asymptotic complexities.
Identify Θ-equivalent functions with experiments.