#include "graph.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char** argv) {
    string filepath = argv[1];
    string starting_node = argv[2]; // needed for BFS Traversal

    Graph * g = new Graph(filepath);
    cout << "Graph (Start Node: Adjacent Nodes):" << endl;
    cout << "========================================================" << endl;
    g->printGraph(cout);


    // BFS Traversal
    cout << endl;
    cout << "BFS Traversal:" << endl;
    cout << "========================================================" << endl;
    vector<vector<Graph::Node>> bfs = BFSTraversal(starting_node, g);    
    for (size_t i = 0; i < bfs.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for (size_t j = 0; j < bfs[i].size(); j++) {
            cout << bfs[i][j] << "\n";
        }
        cout << endl;
    }

    // Kosaraju's Algorithm
    cout << endl;
    cout << "Kosaraju's Algorithm:" << endl;
    cout << "========================================================" << endl;
    vector<vector<Graph::Node>> kosa = kosaraju(g);
    for (size_t i = 0; i < kosa.size(); i++) {
        cout << "Strongly Connected Component " << i + 1 << ": ";
        for (size_t j = 0; j < kosa[i].size(); j++) {
            cout << kosa[i][j] << " ";
        }
        cout << endl;
    }

    // Betweenness Centrality
    cout << endl;
    cout << "Betweenness Centrality: " << endl;
    cout << "========================================================" << endl;
    map<Graph::Node, float> between = betweennessCentrality(g);
    for (auto it = between.begin(); it != between.end(); ++it) {
        cout << "Value of " << it->first << ": " << it->second << endl;
    }
    
    return 0;
}
