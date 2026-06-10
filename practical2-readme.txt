Problem Statement

The goal is to compare the efficiency of Binary Search and Ternary Search algorithms. Both algorithms are used to search for an element in a sorted array, but they differ in the way they split the array at each step:

Binary Search divides the array into two parts.

Ternary Search divides the array into three parts.

We measure the number of comparisons made by each algorithm when searching for an element in arrays of different sizes.

Approach

Implemented Binary Search and Ternary Search functions with counters to track the number of comparisons.

Tested on arrays of sizes:

10, 100, 1000, 10000, 100000


Each array contains integers in sorted order.

Searched for the last element (worst-case scenario).

Displayed results in:

Tabular format (showing comparisons).

ASCII Bar Graph (visual comparison using * for Binary and # for Ternary).

Implementation Details

Binary Search:

Checks middle element of the current interval.

Reduces search space to half.

Time complexity: O(log₂ n).

Ternary Search:

Checks two midpoints in the current interval.

Reduces search space to one-third in each step.

Time complexity: O(log₃ n).

Both algorithms are logarithmic in complexity, but Binary Search usually performs fewer comparisons in practice.

Sample Output

Table of Comparisons:

Comparisons Table:
 n       Binary   Ternary
10      4        4
100     7        6
1000    10       7
10000   14       9
100000  17       11


Graph (ASCII Visualization):

Graph ( * = Binary , # = Ternary )
n=10     | ****  ####
n=100    | *******  ######
n=1000   | **********  #######
n=10000  | **************  #########
n=100000 | *****************  ###########

Key Observations

Binary Search makes slightly more comparisons than Ternary Search in this setup.

In terms of time complexity, both are logarithmic and efficient.

However, Binary Search is generally faster in practice, since Ternary Search performs two comparisons per iteration.

The experiment highlights that fewer theoretical iterations (log₃ n) does not always guarantee better performance.

Conclusion

Both algorithms are efficient for searching in sorted arrays.

Binary Search is usually preferred due to its simplicity and lower constant overhead.

This program provides a clear visual and tabular comparison of their performance.