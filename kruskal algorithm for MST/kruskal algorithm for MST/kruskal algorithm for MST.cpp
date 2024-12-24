#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a struct to represent an edge
struct Edge {
    int u, v, weight;
};

// Compare function for sorting edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}
// Function to find the parent of a node in a disjoint set
int dfs(vector<int>& parent, int u) {
    if (parent[u] != u)
        parent[u] = dfs(parent, parent[u]);
    return parent[u];
}
// Function to union two sets
void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
	// Find the root of each set
    int rootU = dfs(parent, u);
    int rootV = dfs(parent, v);
	// Union by rank
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        }
        else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}
// Function to perform Kruskal's Algorithm
void kruskal(int n, vector<vector<pair<int, int>>>& adjList) {
    vector<Edge> edges;
    // Convert adjacency list to edge list
    for (int u = 0; u < n; ++u) {
        for (auto& p : adjList[u]) {
            if (u < p.first) // Avoid duplicate edges
                edges.push_back({ u, p.first, p.second });
        }
    }
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compare);
    // Initialize disjoint set
    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    cout << "Edges in the MST:\n";

    int mstEdges = 0;
	int mstWeight = 0;
    for (const Edge& edge : edges) {
		// Check if adding the edge will form a cycle
        if (dfs(parent, edge.u) != dfs(parent, edge.v)) {
            cout << edge.u << " -- " << edge.v << " == " << edge.weight << "\n";
			// Union the sets
            unionSets(parent, rank, edge.u, edge.v);
            mstEdges++;
			mstWeight += edge.weight;
        }
        if (mstEdges == n - 1)
            break; // Stop when MST has |V| - 1 edges
    }
	cout << "\n";
	cout << "Total weight of the MST : ";
	cout << mstWeight << "\n";
}

int main() {
    int n, m;
	cout << "Enter the number of vertices : ";
	cin >> n;
	cout << "Enter the number of edges : ";
	cin >> m;
    // Initialize adjacency list
    vector<vector<pair<int, int>>> adjList(n);
	cout << "Enter the edges and their weights : \n";
	for (int i = 0; i < m; i++) {
		int u, v, weight;
		cin >> u >> v >> weight;
		adjList[u].push_back({ v, weight });
		adjList[v].push_back({ u, weight });
	}
    // Perform Kruskal's Algorithm
    kruskal(n, adjList);

    return 0;
}
