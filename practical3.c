#include <stdio.h>

// Function to check weight of two groups of coins
// returns: -1 if left group is lighter, 1 if right group is lighter, 0 if equal


int weigh(int coins[], int left, int mid, int right) {
    int sumLeft = 0, sumRight = 0;
    for (int i = left; i <= mid; i++) sumLeft += coins[i];
    for (int i = mid + 1; i <= right; i++) sumRight += coins[i];

    if (sumLeft < sumRight) return -1;
    else if (sumRight < sumLeft) return 1;
    else return 0;
}

// Recursive function to find defective (lighter) coin

int findDefective(int coins[], int left, int right, int normalWeight) {
    if (left == right) {
        if (coins[left] < normalWeight) return left; // defective found
        else return -1;                            // no defective
    }

    int mid = (left + right) / 2;

    int result = weigh(coins, left, mid, right);

    if (result == -1)                                // left half lighter
        return findDefective(coins, left, mid, normalWeight);
    else if (result == 1)                           // right half lighter
        return findDefective(coins, mid + 1, right, normalWeight);
    else
        return -1;                                  // all equal, no defective coin
}



int main() {
    int n, normalWeight;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter the weights of %d coins:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &coins[i]);

    printf("Enter the normal (correct) coin weight: ");
    scanf("%d", &normalWeight);

    int defectiveIndex = findDefective(coins, 0, n - 1, normalWeight);

    if (defectiveIndex == -1)
        printf("All coins are correct.  No defective coin found.\n");
    else
        printf("Defective coin found at index %d with weight %d\n", defectiveIndex, coins[defectiveIndex]);

    return 0;
}
