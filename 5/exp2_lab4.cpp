
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<bool> visited;

    // DFS function
    void DFS(int u) {
        visited[u] = true;
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                DFS(v);
            }
        }
    }

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        visited.resize(V, false);
    }

    // Add an undirected edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Find connected components
    void findConnectedComponents() {
        int count = 0;

        cout << "Connected Components:\n";

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                count++;

                cout << "Component " << count << ": ";

                DFS(i);

                cout << endl;
            }
        }

        cout << "Total Connected Components = "
             << count << endl;
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findConnectedComponents();

    return 0;
}