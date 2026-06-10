#include <stdio.h>
#include <limits.h>

#define MAX 50

int main() {
    int n, e;
    int graph[MAX][MAX];
    
    printf("enter number of vertices: ");
    scanf("%d", &n);

    // nitializing matrix
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            graph[i][j] = 0;

    printf("enter number of edges: ");
    scanf("%d", &e);

    printf("enter edges in format: u v w\n");
    for(int i=0;i<e;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;   // undirected
    }

    int key[MAX], parent[MAX], visited[MAX];

    for(int i=0;i<n;i++)
        key[i] = INT_MAX, visited[i]=0;

    key[0] = 0;
    parent[0] = -1;

    for(int count=0; count<n-1; count++){
        int min = INT_MAX, u;

        for(int i=0;i<n;i++)
            if(!visited[i] && key[i] < min)
                min = key[i], u=i;

        visited[u] = 1;

        for(int v=0; v<n; v++){
            if(graph[u][v] && !visited[v] && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nedges in MST (Prim):\n");
    int total = 0;
    for(int i=1;i<n;i++){
        printf("%d - %d  : %d\n", parent[i], i, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("\nTotal Weight = %d\n", total);

    return 0;
}
