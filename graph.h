#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

class Graph {
    public:
        typedef string Node;

        /**
         * @brief Edge struct that contains a start and end Node
         * 
         */
        struct Edge {
            Node start_;
            Node end_;
            bool operator== (const Edge& other) const {
                return start_ == other.start_ && end_ == other.end_;
            }
        };

        /**
         * @brief Construct a new Graph object
         * 
         * @param filepath - The filepath containing node/edge data
         */
        Graph(string filepath);
        
        /**
         * @brief Destroy the Graph object
         * 
         */
        ~Graph();

        /**
         * @brief Construct a new Graph object from another Graph
         * 
         * @param g - The Graph to be copied
         */
        Graph(const Graph &g);

        /**
         * @brief Assignment operator
         * 
         * @param g - The Graph to be copied
         * @return Graph& 
         */
        Graph& operator=(const Graph& g);

        /**
         * @brief Equality overloader
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator== (const Graph& other) const;

        /**
         * @brief Inequality overloader
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator!= (const Graph& other) const;

        /**
         * @brief Prints the graph in Node: Adjacent_Node Adjacent_Node ... format
         * 
         * @param output 
         */
        void printGraph(std::ostream& output);

        /**
         * @brief Create a Adjacency List for the current Graph
         * 
         * @param filepath 
         */
        void createAdjacencyList(string filepath);

        /**
         * @brief Get the Adjacency List
         * 
         * @return map<Node, vector<Edge>>& 
         */
        map<Node, vector<Edge>> & getAdjacencyList();

    private:
        map<Node, vector<Edge>> adjacency_list_;

        // Adds a Node to the Graph
        void addNode(Node node);

        // Adds an Edge to the Graph given a specific pair of Nodes
        void addEdge(Node start, Node end);
};
