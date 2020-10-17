#pragma once

// graph class 

#include <vector>
#include <iostream>
#include "Node.h"

class Graph {

public:


	void add_node(Node* add);
	void add_edge(Node* from, Node* to);
	void draw();
	bool is_node_in_graph(Node* u);
	bool is_edge_in_graph(Node* from, Node* to);
	void reset_node_colors();

	// getters 
	std::vector<Node*> get_nodes() {
		return nodes;
	};

private:
	std::vector<Node*> nodes;

	// add class for edges to have weights ? 
	//std::vector<Edge*> edges;
};

 


class UndirectedGraph : public Graph {

public:
	void add_edge(Node* from, Node* to) {
		// check if they're already in the graph?? 
		if (!is_node_in_graph(from)) {
			add_node(from);
		}
		if (!is_node_in_graph(to)) {
			add_node(to);
		}

		(*from).add_in_neighbor(to);
		(*from).add_out_neighbor(to);
		(*to).add_in_neighbor(from);
		(*to).add_out_neighbor(from);
	};


private:
	std::vector<Node*> nodes;
};





#include "WeightedEdge.h"
class WeightedGraph : public Graph {

public :
	void add_edge(WeightedEdge* e);
	void draw();
	std::vector<WeightedEdge*> get_edges() { return edges; };

private : 
	std::vector<WeightedEdge*> edges;

};




// THIS ONE DOESNT WORK RIGHT NOW 
//class DenseGraph : public UndirectedGraph {
//
//public:
//	void add_node(Node* u) {
//		//add_edge from this node to all nodes in the graph
//		if (nodes.size() == 0) {
//			nodes.push_back(u);
//		}
//
//		for (auto& n : nodes) {
//			if (u == n) { continue; };
//			add_edge(u, n);
//		}
//	};
//
//private:
//	std::vector<Node*> nodes;
//};





