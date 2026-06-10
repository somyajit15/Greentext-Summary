#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define M 50   // max number of left vertices
#define N 50   // max number of right vertices

bool bpm(int u, bool bpGraph[M][N], bool seen[N], int matchR[N], int n)
{
    for (int v = 0; v < n; v++)
    {
        if (bpGraph[u][v] && !seen[v])
        {
            seen[v] = true;

            if (matchR[v] < 0 || bpm(matchR[v], bpGraph, seen, matchR, n))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBPM(bool bpGraph[M][N], int m, int n)
{
    int matchR[N];
    memset(matchR, -1, sizeof(matchR));

    int result = 0;

    for (int u = 0; u < m; u++)
    {
        bool seen[N];
        memset(seen, 0, sizeof(seen));

        if (bpm(u, bpGraph, seen, matchR, n))
            result++;
    }

    printf("\nMatched Pairs (Right -> Left):\n");
    for (int i = 0; i < n; i++)
    {
        if (matchR[i] != -1)
            printf("Right %d <--> Left %d\n", i, matchR[i]);
    }

    return result;
}

int main()
{
    int m, n;
    bool bpGraph[M][N];

    printf("Enter number of vertices on LEFT set: ");
    scanf("%d", &m);

    printf("Enter number of vertices on RIGHT set: ");
    scanf("%d", &n);

    printf("Enter bipartite graph adjacency matrix (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &bpGraph[i][j]);

    printf("\nMaximum Bipartite Matching = %d\n", maxBPM(bpGraph, m, n));

    return 0;
}
