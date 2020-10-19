#pragma once

#include "Graph.h"

// general connectivity 
void search(Node* u);
bool st_connectivity(Graph* G, Node* u, Node* v);

// DFS
void DFS_visit(Graph* G, std::vector<Node*> parents , Node* u);
std::vector<Node*> DFS(Graph* G);


// BFS
Graph BFS(Graph* G, Node* start);

// Dijkstra's







// Utils 

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