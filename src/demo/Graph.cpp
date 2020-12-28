
#include "Graph.h"

////////////////////////////////////////////////////////////////////////
// Typical directed graph functionality
////////////////////////////////////////////////////////////////////////



// add a node into the adjacency list
void Graph::add_node(Node* add) {
	nodes.push_back(add);
};




// add an edge between two nodes in the adjacency list 
//		adds the nodes to the graph if they aren't already in it
void Graph::add_edge(Node* from, Node* to){
	if (!is_node_in_graph(from)) {
		add_node(from);
	}
	if (!is_node_in_graph(to)) {
		add_node(to);
	}
	if (!is_edge_in_graph(from, to)) {
		(*from).add_out_neighbor(to);
		(*to).add_in_neighbor(from);
	}
}




// print out the adjacency list 
//		each row will always end in "null" 
void Graph::draw() {
	for (auto& n : nodes) {
		std::cout << (*n).get_val() << " : " << std::flush;
		for (auto& nout : (*n).get_out_neighbors()) {
			std::cout << (*nout).get_val() << " , " << std::flush;
		}
		std::cout << "null" << std::endl;
	}
}




// check if a node is already present in the graph
bool Graph::is_node_in_graph(Node* u) {
	for (auto& n : nodes) {
		if (u == n) {
			return true;
		}
	}
	return false;
}



// check if an edge is already present in the graph
bool Graph::is_edge_in_graph(Node* from, Node* to){
	for (auto& n : (*from).get_out_neighbors()) {

		if (n == to) {
			return true;
		}
	}
	return false;
}


// after a search, set the nodes' color back to the default true value
void Graph::reset_node_colors(){
	for (auto& n : nodes) {
		(*n).set_color(true);
	}
}




////////////////////////////////////////////////////////////////////////
// weighted graph
////////////////////////////////////////////////////////////////////////


// add an edge like a normal graph, but also add it to the map of weights 
//template <class T>
//void WeightedGraph<T>::add_edge(Node* from, Node* to, T weight)

// get the weight of an edge from u to v 
//template <class T>
//T  WeightedGraph<T>::get_edge_weight(Node* from, Node* to)




// add weighted edge 
// SHOULD JUST TAKE A WEIGHTED EDGE REFERENCE
//void WeightedGraph::add_edge(Node* from, Node* to, double weight){
//	if (!is_node_in_graph(from)) {
//		add_node(from);
//	}
//	if (!is_node_in_graph(to)) {
//		add_node(to);
//	}
//	if (!is_edge_in_graph(from, to)) {
//		(*from).add_out_neighbor(to);
//		(*to).add_in_neighbor(from);
//		WeightedEdge e = WeightedEdge::WeightedEdge(from, to, weight);
//		edges.push_back(&e);
//	}
//}


//void WeightedGraph::add_edge(WeightedEdge* e) {
//	Node* from = (*e).get_parent();
//	Node* to = (*e).get_child();
//	if (!is_node_in_graph(from)) {
//		add_node(from);
//	}
//	if (!is_node_in_graph(to)) {
//		add_node(to);
//	}
//	if (!is_edge_in_graph(from, to)) {
//		(*from).add_out_neighbor(to);
//		(*to).add_in_neighbor(from);
//		edges.push_back(e);
//	}
//}



// print out all edges with weights
//void WeightedGraph::draw() {
//	for (auto& e : edges) {
//		std::cout << (*(*e).get_parent()).get_val() << "  --"  << (*e).get_weight() << "-->  " << std::flush;
//		std::cout << (*(*e).get_child()).get_val()  <<  std::endl;
//	}
//}