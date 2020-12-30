#pragma once

#include "Graph.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////
// Unweighted graph algs 
//////////////////////////////////////////////////////////////////////////////////////////////////////


// general connectivity 
void search(Node* u);
bool st_connectivity(Graph* G, Node* u, Node* v);

// DFS
void DFS_visit(Graph* G, std::vector<Node*> parents , Node* u);
std::vector<Node*> DFS(Graph* G);


// BFS
Graph BFS(Graph* G, Node* start);




//////////////////////////////////////////////////////////////////////////////////////////////////////
// Weighted graph algs 
//////////////////////////////////////////////////////////////////////////////////////////////////////



// used for making a min heap of nodes --> relates a node to its adjacent edge with the smallest weight
typedef std::pair<Node*, int> NodeEdgePair; // https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/ had to check this out to fix my min heap ... RIP 
// needs to be templated :(



// Prim's MST algorithm 
// TODO : figure out how to get the templating right ... Ideally wouldn't have this implemented in the headers file
//
// also still need to reconstruct the MST weighted graph from the parent relations 
//
// maybe figure out a better way to set initial min weights to inf
//
template <class T>
//using NodeEdgePair = std::pair<Node*, T>;
WeightedGraph<T> Prim_MST(WeightedGraph<T>* G, Node* root) {
//void Prim_MST(WeightedGraph<T>* G, Node* root) {

	WeightedGraph<T> MST;
	std::map<Node*, T> min_weight;
	std::map<Node*, Node*> parent;


	std::set<Node*> s; // no find in priority queue so have to also maintain a set that represents the nodes not contained in the MST :(
	std::priority_queue< NodeEdgePair, std::vector <NodeEdgePair>, std::greater<NodeEdgePair> > min_heap;
	for (auto& n : (*G).get_nodes()) {
		min_weight[n] = 1e6; // not sure the best way to do infinity, but this is a little hacky
		parent[n] = nullptr;
		s.insert(n); // no nodes start in the MST
	};


	min_heap.push(std::make_pair(root, 0));
	min_weight[root] = 0;
	while (!min_heap.empty()) {
		Node* u = min_heap.top().first; // extract the min 
		min_heap.pop();
		s.erase(u);
		for (auto& v : (*u).get_out_neighbors()) {
			T w = G->get_edge_weight(u, v);
			if (  (s.find(v) != s.end()) and (w < min_weight[v])  ) { 
				min_weight[v] = w;
				parent[v] = u;
				//if ((*u).get_val() == 2.0) { std::cout << (*(parent[v])).get_val() << "<-" << min_weight[v] << "->" << (*v).get_val() << std::endl; };
				//if ((*u).get_val() == 6.0) { std::cout << (*(parent[v])).get_val() << "<-" << min_weight[v] << "->" << (*v).get_val() << std::endl; };
				min_heap.push(std::make_pair(v, min_weight[v]));
			}
		}
	}


	// print result
	for (auto& n : (*G).get_nodes()) {
		if (parent[n] != nullptr){ 
			std::cout << (*n).get_val() << "<----" << (*(parent[n])).get_val() << std::endl;
		}
		else {
			std::cout << (*n).get_val() << "<----" << "null" << std::endl;
		}
	};

	// TODO : Fix this part ... not sure that this is the actual way to do this
	// construct the MST from the parent relationships
	for (auto& n : (*G).get_nodes()) {
		if (parent[n] != nullptr) {
			MST.add_edge(parent[n], n, min_weight[n]);
			MST.add_edge(n, parent[n], min_weight[n]);
		}
	};

	return MST;
};


// Kruskal's
//WeightedGraph Kruskal_MST(WeightedGraph* G);




// Dijkstra's








//////////////////////////////////////////////////////////////////////////////////////////////////////
// Utils
//////////////////////////////////////////////////////////////////////////////////////////////////////


// retruns index of an element 
template <class T>
int get_index(std::vector<T> v, T K)
{
	auto it = find(v.begin(), v.end(), K);
	if (it != v.end()) { 	
		return distance(v.begin(), it);
	}
	else {
		return -1;
	}
}

