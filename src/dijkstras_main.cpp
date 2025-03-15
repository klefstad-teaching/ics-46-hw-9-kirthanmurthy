#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string f = "src/small.txt"; 
    Graph G;
    file_to_graph(f, G);
    vector<int> previous(G.numVertices, -1);
    vector<int> dist = dijkstra_shortest_path(G, 0, previous);
    for (int v = 0; v < G.numVertices; ++v) {
        vector<int> path = extract_shortest_path(dist, previous, v);
        print_path(path, dist[v]);
    }
    return 0;
}