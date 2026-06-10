#include <stdio.h>

#define MAX 50

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

int find(int x) {
    while(parent[x] != x)
        x = parent[x];
    return x;
}

void unionSet(int x, int y) {
    int a = find(x);
    int b = find(y);
    parent[a] = b;
}

int main() {
    int n, e;
    Edge edges[MAX], result[MAX];

    printf("enter number of vertices: ");
    scanf("%d", &n);

    printf("enter number of edges: ");
    scanf("%d", &e);

    printf("enter edges (u v w):\n");
    for(int i=0;i<e;i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);

    for(int i=0;i<n;i++)
        parent[i]=i;

    // sort edges by weight
    for(int i=0;i<e;i++){
        for(int j=i+1;j<e;j++){
            if(edges[i].w > edges[j].w){
                Edge t = edges[i];
                edges[i]=edges[j];
                edges[j]=t;
            }
        }
    }

    int count = 0, total = 0;

    for(int i=0;i<e;i++) {
        int root1 = find(edges[i].u);
        int root2 = find(edges[i].v);

        if(root1 != root2){
            result[count++] = edges[i];
            total += edges[i].w;
            unionSet(root1, root2);
        }
    }

    printf("\nedges in Mst (Kruskal):\n");
    for(int i=0;i<count;i++)
        printf("%d - %d : %d\n", result[i].u, result[i].v, result[i].w);

    printf("\ntotal weight = %d\n", total);

    return 0;
}
