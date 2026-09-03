#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    int timer;

    void DFS(int u, int parent, vector<int>& tin,
             vector<int>& low, vector<bool>& visited,
             vector<bool>& articulation) {

        visited[u] = true;
        tin[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (v == parent)
                continue;

            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } 
            else {
                DFS(v, u, tin, low, visited, articulation);

                low[u] = min(low[u], low[v]);

                // u is an articulation point
                if (parent != -1 && low[v] >= tin[u])
                    articulation[u] = true;

                children++;
            }
        }

        // Root of DFS tree is articulation point
        if (parent == -1 && children > 1)
            articulation[u] = true;
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findArticulationPoints() {
        vector<int> tin(V, -1), low(V, -1);
        vector<bool> visited(V, false);
        vector<bool> articulation(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i])
                DFS(i, -1, tin, low, visited, articulation);
        }

        cout << "Articulation Points: ";

        bool found = false;
        for (int i = 0; i < V; i++) {
            if (articulation[i]) {
                cout << i << " ";
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << endl;
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

    g.findArticulationPoints();

    return 0;
}