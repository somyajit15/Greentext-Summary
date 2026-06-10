Defective Coin Problem:

Problem Statement

We are given n coins. All coins are expected to have the same weight, except possibly one defective coin which is lighter than the others.
If all coins have the same weight, then there is no defective coin.
The task is to design an algorithm using Divide and Conquer to identify the defective coin in O(log n) time.

---------------------------------------------------------------------------------------------------------------

Approach

Divide the coins into two groups (left and right halves).

Weigh both groups:

If the left side is lighter, the defective coin lies in the left group.
If the right side is lighter, the defective coin lies in the right group.
If both sides are equal, there is no defective coin.


Recurse into the lighter half until only one coin remains.

If that coin is lighter than the normal weight, it is defective. Otherwise, all coins are perfect.

This approach reduces the problem size by half in each step, achieving O(log n) complexity.

---------------------------------------------------------------------------------------------------------------

Implementation

The program simulates weighing by summing the weights of coins in each half.
A recursive function findDefective() applies the divide and conquer strategy to locate the defective coin (if present).

Example:

Input

n = 6  
coins = [10, 10, 9, 10, 10, 10]  
normal weight = 10

---------------------------------------------------------------------------------------------------------------
Process

Compare [10, 10, 9] vs [10, 10, 10] : left side lighter

Compare [10, 10] vs [9] : right side lighter

Defective coin found at index 2 with weight 9


Output:

Defective coin found at index 2 with weight 9
