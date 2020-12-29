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


// Prim's 
// TODO : something isn't right with the min heap here ... 
//
// also need to figure out how to get the templating right ... Ideally wouldn't have this implemented in the headers file
//
// ALSO need to reconstruct the MST weighted graph from the parent relations 
//
template <class T>
//WeightedGraph<T> Prim_MST(WeightedGraph<T>* G, Node* root) {
void Prim_MST(WeightedGraph<T>* G, Node* root) {

	//WeightedGraph<T> MST;
	std::map<Node*, T> min_weight;
	std::map<Node*, Node*> parent;

	// fill a queue with all the nodes in the graph; maintain a dictionary of the min edge weight for each node 
	std::set<Node*> s; // no find in priority queue so have to also maintain a set that represents the nodes not contained in the MST :(
	//auto cmp = [&](Node* u, Node* v) { return min_weight[u] > min_weight[v]; };
	//std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> q(cmp); // min heap of weights for each node 
	std::priority_queue< NodeEdgePair, std::vector <NodeEdgePair>, std::greater<NodeEdgePair> > min_heap;
	for (auto& n : (*G).get_nodes()) {
		min_weight[n] = 1e6; // not sure the best way to do infinity, but this is a little hacky
		parent[n] = nullptr;
		//q.push(n);
		s.insert(n); // nothing starts in the MST
	};



	// while the queue isn't empty, inspect adjacencies of current node and add the cheapest edge to the output graph
	min_heap.push(std::make_pair(root, 0));
	min_weight[root] = 0;
	while (!min_heap.empty()) {
		Node* u = min_heap.top().first; // extract the min 
		min_heap.pop();
		s.erase(u);
		for (auto& v : (*u).get_out_neighbors()) {
			T w = G->get_edge_weight(u, v);
			//std::cout << (s.find(v) != s.end()) << " & " << w << " ? " << min_weight[v] << std::endl;
			if (  (s.find(v) != s.end()) and (w < min_weight[v])  ) { // not finding things in the set or map???
				std::cout << (*u).get_val() << std::endl;
				min_weight[v] = w;
				parent[v] = u;
				min_heap.push(std::make_pair(v, min_weight[v]));
			}
		}
	}


	// JUST FOR NOW PRINT OUT THE PARENT RESULTS
	for (auto& n : (*G).get_nodes()) {
		if (parent[n] != nullptr){ 
			std::cout << (*n).get_val() << "----" << (*(parent[n])).get_val() << std::endl;
		}
		else {
			std::cout << (*n).get_val() << "----" << "null" << std::endl;
		}
	};


	// construct the MST from the parent relationships


	//return MST;
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

