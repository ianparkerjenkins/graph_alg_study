#pragma once

// graph class 

#include <vector>
#include <map>
#include <limits>
#include <set>
#include <queue>
#include <iostream>
#include "Node.h"
//#include "WeightedEdge.h"


class Graph {

public:


	void add_node(Node* add);
	void add_edge(Node* from, Node* to);
	void draw();
	bool is_node_in_graph(Node* u);
	bool is_edge_in_graph(Node* from, Node* to);
	void reset_node_colors();

	// getters 
	std::vector<Node*> get_nodes() { return nodes;	};

private:
	std::vector<Node*> nodes; // each node will contain the information about it's inward and outward neighbors 

};

 


class UndirectedGraph : public Graph {

public:
	void add_edge(Node* from, Node* to) {
		if (!is_node_in_graph(from)) {
			add_node(from);
		}
		if (!is_node_in_graph(to)) {
			add_node(to);
		}

		// treat undirected edges as bidirectional --> each node is both an in and out neighbor of each other 
		(*from).add_in_neighbor(to);
		(*from).add_out_neighbor(to);
		(*to).add_in_neighbor(from);
		(*to).add_out_neighbor(from);
	};


private:
	std::vector<Node*> nodes;
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// weighted graph classes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class WeightedEdge {

public:

	WeightedEdge(Node* from, Node* to, double w_) : parent(from), child(to), weight(w_) {};

	// setters 
	void set_weight(double w_) { weight = w_; };
	void set_parent(Node* p_) { parent = p_; };
	void set_child(Node* c_) { child = c_; };

	// getters 
	double get_weight() { return weight; };
	Node* get_parent() { return parent; };
	Node* get_child() { return child; };

private:

	double weight{ 0 }; // TODO : Template type the weight
	Node* parent;
	Node* child;

};

// template for the datatype of the weights, maybe this is overkill ... 
template <class T> // all weights for a graph must be of the same type... that sounds fairly reasonable

class WeightedGraph : public Graph {

public:

	void add_edge(Node* from, Node* to, T weight) {
		if (!is_node_in_graph(from)) {
			add_node(from);
		}
		if (!is_node_in_graph(to)) {
			add_node(to);
		}
		if (!is_edge_in_graph(from, to)) {
			(*from).add_out_neighbor(to);
			(*to).add_in_neighbor(from);
			weights[from][to] = weight;
			WeightedEdge e = WeightedEdge::WeightedEdge(from, to, weight);
			edges.push_back(&e);
		}
	};

	T get_edge_weight(Node* from, Node* to) {
		if (weights.find(from) == weights.end()) {
			// starting node not found
			std::cout << " Starting node not found when looking up edge weight " << std::endl;
			return std::numeric_limits<T>::infinity();
		}
		else {
			if (weights[from].find(to) == weights[from].end()) {
				// edge not found
				std::cout << " Edge not found when looking up edge weight " << std::endl;
				return std::numeric_limits<T>::infinity();
			}
			else {
				// found
				return weights[from][to];
			};
		};
	};


	std::vector<WeightedEdge*> get_edges() { return edges; };


private:
	std::vector<WeightedEdge*> edges; // some algs may want to get through or sort all edges in the graph, so making this for conviniece 
	std::map< Node*, std::map< Node*, T > >  weights;

};



// Wanted to change the way that this works to be more useful ...
//		just have a normal graph with a lookup for the weight of each added edge 
//#include "WeightedEdge.h"
//class WeightedGraph : public Graph {
//
//public :
//	void add_edge(WeightedEdge* e);
//	void draw();
//	std::vector<WeightedEdge*> get_edges() { return edges; };
//
//private : 
//	std::vector<WeightedEdge*> edges;
//};




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




