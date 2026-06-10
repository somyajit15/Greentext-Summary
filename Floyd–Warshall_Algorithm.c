#include <stdio.h>
#define INF 9999

int main() {
    int n;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int dist[n][n];

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            if (dist[i][j] == 0 && i != j)
                dist[i][j] = INF;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("\nAll Pair Shortest Path Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf(" INF ");
            else
                printf("%4d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
