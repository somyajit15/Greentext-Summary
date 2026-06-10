#include <stdio.h>
#define INF 9999

int main() {
    int n, source;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int cost[n][n], dist[n], visited[n];

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INF;
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    for (int i = 0; i < n; i++) {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;

    for (int count = 1; count < n; count++) {
        int min = INF, u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[u] + cost[u][i] < dist[i]) {
                dist[i] = dist[u] + cost[u][i];
            }
        }
    }

    printf("\nShortest distances from source %d:\n", source);
    for (int i = 0; i < n; i++) {
        printf("To %d = %d\n", i, dist[i]);
    }

    return 0;
}

