#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

// ---------- Disjoint Set Union for Kruskal ----------
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;

        return true;
    }
};

// ---------- Prim's Algorithm ----------
void primMST(const vector<vector<pair<int, int>>> &graph, int n) {
    vector<bool> visited(n, false);
    vector<int> key(n, 1e9);
    vector<int> parent(n, -1);

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;

        // Find the unvisited vertex with minimum key
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        visited[u] = true;

        // Update adjacent vertices
        for (auto [v, weight] : graph[u]) {
            if (!visited[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    int totalWeight = 0;

    cout << "\nMST using Prim's Algorithm:\n";
    cout << "Edge\tWeight\n";

    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << "\t"
             << key[i] << endl;
        totalWeight += key[i];
    }

    cout << "Total weight = " << totalWeight << endl;
}

// ---------- Kruskal's Algorithm ----------
void kruskalMST(vector<Edge> edges, int n) {
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) {
             return a.weight < b.weight;
         });

    DSU dsu(n);

    int totalWeight = 0;
    int edgeCount = 0;

    cout << "\nMST using Kruskal's Algorithm:\n";
    cout << "Edge\tWeight\n";

    for (auto edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            cout << edge.u << " - " << edge.v
                 << "\t" << edge.weight << endl;

            totalWeight += edge.weight;
            edgeCount++;

            if (edgeCount == n - 1)
                break;
        }
    }

    cout << "Total weight = " << totalWeight << endl;
}

// ---------- Main Function ----------
int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<pair<int, int>>> graph(n);
    vector<Edge> edges;

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});

        edges.push_back({u, v, w});
    }

    primMST(graph, n);
    kruskalMST(edges, n);

    return 0;
}