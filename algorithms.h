#pragma once

#include <vector>
#include <stack>
#include "graph.h"

using namespace std;

/**
 * @brief Performs Breadth-First-Search based on a start node and the adjacency list. Does not add in elements if elements are not connected
 * 
 * @param start 
 * @param adj_list 
 * @param visited 
 * @return vector<Graph::Node> 
 */
vector<Graph::Node> BFSTraversal(Graph::Node start, map<Graph::Node, vector<Graph::Edge>> & adj_list, map<Graph::Node, bool> & visited);

 /**
  * @brief Performs Breadth-First-Search based on a start node but also adds in elements if they are not connected
  * 
  * @param start 
  * @param adj_list 
  * @param visited 
  * @return vector<Graph::Node> 
  */
vector<vector<Graph::Node>> BFSTraversal(Graph::Node start, Graph * graph);

/**
 * @brief Performs Kosaraju's Algorithm for finding Strongly Connected Components in a graph. Returns a vector of vectors that contain the Nodes in each SCC
 * 
 * @param graph 
 * @return vector<vector<Graph::Node>> 
 */
vector<vector<Graph::Node>> kosaraju(Graph * graph);

/**
 * @brief Flips the direction all of the edges in the directed graph and returns the reversed graph
 * 
 * @param adj_list 
 * @return map<Graph::Node, vector<Graph::Edge>> 
 */
map<Graph::Node, vector<Graph::Edge>> reverseAdjacencyList(map<Graph::Node, vector<Graph::Edge>> & adj_list);

/**
 * @brief Performs Depth-First-Search on the Graph
 * 
 * @param node 
 * @param s 
 * @param adj_list 
 * @param visited 
 * @param isFirst 
 * @param scc 
 */
void DFS(Graph::Node node, stack<Graph::Node> & s, map<Graph::Node, vector<Graph::Edge>> & adj_list, map<Graph::Node, bool> & visited, bool isFirst, vector<Graph::Node> & scc);

/**
 * @brief Calculate the Betweenness Centrality score of every Node in the graph using Brandes' Algorithm. Returns a map of the betweenness score of every node
 * 
 * @param graph 
 * @return map<Graph::Node, float> 
 */
map<Graph::Node, float> betweennessCentrality(Graph * graph);

/**
 * @brief Finds the shortest path between a start node and every other node in the graph. Returns a map of all the shortest paths for a given start node to every other node
 * 
 * @param start 
 * @param graph 
 * @return map<Graph::Node, vector<Graph::Node>> 
 */
map<Graph::Node, vector<Graph::Node>> shortestPath(Graph::Node start, Graph * graph);

