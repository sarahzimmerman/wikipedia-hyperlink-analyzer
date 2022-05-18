#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <stdexcept>

using namespace std;

Graph::Graph(string filepath) {
    createAdjacencyList(filepath);
}

Graph::~Graph() {   }

Graph& Graph::operator=(const Graph& g) {
    adjacency_list_ = g.adjacency_list_;
    return *(this);
}

void Graph::createAdjacencyList(string filepath) {
    ifstream infile(filepath);

    if (!infile || infile.peek() == ifstream::traits_type::eof()) {
        throw std::invalid_argument( "Error during parsing" );
    }

    string line;
    string delimiter = ",";
    // Parse each line, where the format is "Start Node,End Node"
    while (getline(infile, line)) {
        size_t pos = line.find(delimiter);

        if (pos == string::npos) {
            throw std::invalid_argument( "Malformed data" );
        }

        string key = line.substr(0, line.find(delimiter));
        string value = line.substr(line.find(delimiter) + 1, line.length());
        
        addNode(key);
        addNode(value);
        addEdge(key, value);
    }
}

void Graph::addNode(Node node) {
    adjacency_list_.insert({node, vector<Edge>(0)});
}

void Graph::addEdge(Node start, Node end) {
    vector<Edge> & edges = adjacency_list_.at(start);
    for (Edge edge : edges) {
        if (edge.end_ == end) {
            return;
        }
    }

    Edge edge;
    edge.start_ = start;
    edge.end_ = end;
    edges.push_back(edge);
}

map<Graph::Node, vector<Graph::Edge>> & Graph::getAdjacencyList() {
    return adjacency_list_;
}

void Graph::printGraph(std::ostream& output) {
    for (auto pair : adjacency_list_) {
        output << pair.first << ": ";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
            if (std::next(it) != pair.second.end()) {
                output << it->end_ << " ";
            } else {
                output << it->end_;
            }
        }
        output << endl;
    }
}

bool Graph::operator== (const Graph& other) const {
    return adjacency_list_.size() == other.adjacency_list_.size()
        && std::equal(adjacency_list_.begin(), adjacency_list_.end(), other.adjacency_list_.begin());
}

bool Graph::operator!= (const Graph& other) const {
    return !(*(this) == other);
}

Graph::Graph(const Graph &g) {
    adjacency_list_ = g.adjacency_list_;
}
