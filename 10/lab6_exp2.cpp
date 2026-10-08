
#include <stdio.h>
#define INF 99999

struct Edge
{
    int src, dest, weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int source)
{
    int dist[V];
    int i, j;

    // Initialize distances
    for (i = 0; i < V; i++)
        dist[i] = INF;

    dist[source] = 0;

    // Relax all edges V-1 times
    for (i = 1; i < V; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF &&
                dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Detect negative-weight cycle
    for (j = 0; j < E; j++)
    {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF &&
            dist[u] + w < dist[v])
        {
            printf("\nNegative-weight cycle detected!\n");
            return;
        }
    }

    // Print shortest distances
    printf("\nShortest distances from source %d:\n", source);

    for (i = 0; i < V; i++)
    {
        if (dist[i] == INF)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }

    printf("\nNo negative-weight cycle reachable from source.\n");
}

int main()
{
    int V, E, source, i;
    struct Edge edges[100];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (source destination weight):\n");

    for (i = 0; i < E; i++)
    {
        scanf("%d %d %d",
              &edges[i].src,
              &edges[i].dest,
              &edges[i].weight);
    }

    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);

    bellmanFord(edges, V, E, source);

    return 0;
}
