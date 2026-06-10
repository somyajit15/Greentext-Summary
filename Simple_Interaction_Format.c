#include <stdio.h>

int main() {
    int n, e;
    int u, v, w;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int adj[n][n];

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges in SIF format (u v weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;   // Remove this line for directed graph
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}
