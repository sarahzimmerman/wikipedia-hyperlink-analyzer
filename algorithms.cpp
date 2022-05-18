#include "algorithms.h"
#include <map>
#include <queue>

#include <iostream>
#include <algorithm>

using namespace std;

vector<Graph::Node> BFSTraversal(Graph::Node start, map<Graph::Node, vector<Graph::Edge>> & adj_list, map<Graph::Node, bool> & visited) {
    vector<Graph::Node> result;
    queue<Graph::Node> q;
    q.push(start);
    visited.at(start) = true;
    
    while (!q.empty()) {
        Graph::Node curr = q.front();
        q.pop();
        result.push_back(curr);
        for (size_t i = 0; i < adj_list.at(curr).size(); i++) {
            if (!visited.at(adj_list.at(curr)[i].end_)) {
                q.push(adj_list.at(curr)[i].end_);
                visited.at(adj_list.at(curr)[i].end_) = true;
            }
        }
    }

    return result;
}

vector<vector<Graph::Node>> BFSTraversal(Graph::Node start, Graph * graph) {
    map<Graph::Node, bool> visited;
    map<Graph::Node, vector<Graph::Edge>> adj_list = graph->getAdjacencyList();
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        visited.insert({it->first, false});
    }

    vector<vector<Graph::Node>> result;
    //Calls standard BFS on the start node
    result.push_back(BFSTraversal(start, adj_list, visited));

    //Calls BFS on every node not in the same connected component
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        if (!(it->second)) {
            result.push_back(BFSTraversal(it->first, adj_list, visited));
        }
    }
    
    return result;
 }


 vector<vector<Graph::Node>> kosaraju(Graph * graph) {
    // Setup
    vector<vector<Graph::Node>> result;
    stack<Graph::Node> s;

    map<Graph::Node, bool> visited;
    map<Graph::Node, vector<Graph::Edge>> adj_list = graph->getAdjacencyList();
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        visited.insert({it->first, false});
    }

    map<Graph::Node, bool> reverse_visited;
    map<Graph::Node, vector<Graph::Edge>> reverse_adj_list = reverseAdjacencyList(adj_list);
    for (auto it = reverse_adj_list.begin(); it != reverse_adj_list.end(); ++it) {
        reverse_visited.insert({it->first, false});
    }

    // Start of Kosaraju's algorithm
    // First DFS
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        if (!it->second) {
            vector<Graph::Node> placeholder;
            DFS(it->first, s, adj_list, visited, true, placeholder);
        }
        
    }

    // Second DFS on reversed graph
    while (!s.empty()) {
        Graph::Node currNode = s.top();
        s.pop();

        if (!reverse_visited.at(currNode)) {
            vector<Graph::Node> scc;
            DFS(currNode, s, reverse_adj_list, reverse_visited, false, scc);
            sort(scc.begin(), scc.end());
            result.push_back(scc);
        }
    }

    return result;
 }

map<Graph::Node, vector<Graph::Edge>> reverseAdjacencyList(map<Graph::Node, vector<Graph::Edge>> & adj_list) {
    // Must initialize with empty vector to avoid missing nodes during reversal
    map<Graph::Node, vector<Graph::Edge>> reversed;
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        reversed.insert({it->first, vector<Graph::Edge>(0)});
    }

    // Reversal
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        for (Graph::Edge edge : it->second) {
            Graph::Node start = edge.start_;
            Graph::Node end = edge.end_;

            Graph::Edge e;
            e.start_ = end;
            e.end_ = start;
            reversed.at(end).push_back(e);
        }
    }

    return reversed;
}

void DFS(Graph::Node node, stack<Graph::Node> & s, map<Graph::Node, vector<Graph::Edge>> & adj_list, map<Graph::Node, bool> & visited, bool isFirst, vector<Graph::Node> & scc) {
    visited.at(node) = true;

    // If second iteration of DFS, add to strongly connected component
    if (!isFirst) {
        scc.push_back(node);
    }

    // Calls DFS on all adjacent nodes that have not been visited yet
    vector<Graph::Edge> edges = adj_list.at(node);
    for (size_t i = 0; i < edges.size(); i++) {
        Graph::Node currNeighbor = edges[i].end_;
        if (!visited.at(currNeighbor)) {
            DFS(currNeighbor, s, adj_list, visited, isFirst, scc);
        }
    }
    
    // If first iteration of DFS, push node into DFS order
    if (isFirst) {
        s.push(node);
    }
}

map<Graph::Node, float> betweennessCentrality(Graph * graph) {
    //Setup
    map<Graph::Node, float> betweenness;
    map<Graph::Node, vector<Graph::Edge>> adj_list = graph->getAdjacencyList();
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        betweenness.insert({it->first, 0.0});
    }
    int num_paths = 0;

    //Start of finding the betweenness centrality
    //Concurrently counts the number of paths and keeps track of interior nodes
    for (auto start = betweenness.begin(); start != betweenness.end(); ++start) {
        map<Graph::Node, vector<Graph::Node>> paths_from = shortestPath(start->first, graph);
        for (auto it = paths_from.begin(); it != paths_from.end(); ++it) {
            if (it->second.size() == 2) {
                num_paths++;
            } else if (it->second.size() > 2) {
                num_paths++;
                for (unsigned index = 1; index < it->second.size() - 1; index++) {
                    betweenness.at(it->second[index])++;
                }
            }
        }
    }
    //std::cout << "Num of paths" << num_paths<< std::endl;
    //Divides the interior count by the total number of paths
    for (auto start = betweenness.begin(); start != betweenness.end(); ++start) {
        start->second /= num_paths;
    }

    return betweenness;
}   

map<Graph::Node, vector<Graph::Node>> shortestPath(Graph::Node start, Graph * graph){
    //Setup
    map<Graph::Node, bool> visited;
    map<Graph::Node, vector<Graph::Edge>> adj_list = graph->getAdjacencyList();
    vector<Graph::Node> path;
    map<Graph::Node, vector<Graph::Node>> all_paths;
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        visited.insert({it->first, false});
        all_paths.insert({it->first, vector<Graph::Node>()});
    }
    
    //Start of BFS
    queue<Graph::Node> q;
    q.push(start);
    visited.at(start) = true;
    
    while (!q.empty()) {
        Graph::Node curr = q.front();
        q.pop();
        for (size_t i = 0; i < adj_list.at(curr).size(); i++) {
            if (!visited.at(adj_list.at(curr)[i].end_)) {
                visited.at(adj_list.at(curr)[i].end_) = true;
                q.push(adj_list.at(curr)[i].end_);

                //Keeps track of the shortest path to get to the node last added to the queue
                for (unsigned j = 0 ; j < all_paths.at(curr).size(); j++) {
                    all_paths.at(adj_list.at(curr)[i].end_).push_back(all_paths.at(curr)[j]);
                }
                all_paths.at(adj_list.at(curr)[i].end_).push_back(curr);
            }
        }
    }

    //Adds the destination node to the path
    for (auto it = all_paths.begin(); it != all_paths.end(); ++it) {
        if (it->second.size() > 0) {
            it->second.push_back(it->first);
        }
    }
    
    return all_paths;
}
