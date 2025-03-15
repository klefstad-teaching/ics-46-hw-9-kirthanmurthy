#include "dijkstras.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    int vertex;
    int weight;
};

class compareNode {
public:
    bool operator()(const Node& a, const Node& b) const {
        return a.weight > b.weight;  
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    previous.resize(n, -1);
    dist[source] = 0;
    priority_queue<Node, vector<Node>, compareNode> pq;
    pq.push({source, 0});
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }
    return dist;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (destination < 0 || destination >= distances.size() || distances[destination] == INF) {
        return path;
    }
    int cur = destination;
    while (cur != -1) {
        path.insert(path.begin(), cur);
        cur = previous[cur];
    }
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found\n";
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i];
    }
    cout << "\nTotal cost is " << total << endl;
}