#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int price[n];

    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }

    int minPrice = price[0];
    int maxProfit = 0;

    for (int i = 1; i < n; i++) {
        if (price[i] < minPrice) {
            minPrice = price[i];
        }

        int profit = price[i] - minPrice;

        if (profit > maxProfit) {
            maxProfit = profit;
        }
    }

    cout << maxProfit;

    return 0;
}