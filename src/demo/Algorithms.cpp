

#include "Algorithms.h"
#include <queue>
#include <set>





///////////////////////////////////////////////////////////////////////
//  General connectivity
///////////////////////////////////////////////////////////////////////


// recursively search the graph for a node; essentially a DFS sub-tree
//		subroutine for st_connectivity
void search(Node* u) {
	//std::cout << " Searching node : " << (*u).get_val() << std::endl;
	(*u).set_color(false);
	for (auto& v : (*u).get_out_neighbors()) {
		search(v);
	}
};

// return true if the nodes v is reachable from u are connected in G
// return false if u or v aren't present in G or if they aren't connected
bool st_connectivity(Graph* G, Node* u, Node* v) {
	if (!(*G).is_node_in_graph(u)) {
		std::cout << "This node isn't even in the graph" << std::endl;
		return false;
	}
	if (!(*G).is_node_in_graph(v)) {
		std::cout << "This node isn't even in the graph" << std::endl;
		return false;
	}
	search(u);
	bool connectivity = !(*v).get_color();
	(*G).reset_node_colors();
	return connectivity;
};







///////////////////////////////////////////////////////////////////////
//  DFS 
///////////////////////////////////////////////////////////////////////


// recursively search the graph for a node
//		subroutine for DFS
void DFS_visit(Graph* DFS_tree, Node* u) {
	//std::cout << " DFS visiting node : " << (*u).get_val() << std::endl;
	(*u).set_color(false);
	for (auto& v : (*u).get_out_neighbors()) {
		(*DFS_tree).add_edge(u, v);
		DFS_visit(DFS_tree, v);
	}
};


// main call to run depth first search
//		should probably return a DFS tree ... std::vector<Node*>
Graph DFS(Graph* G) {
	Graph DFS_tree;
	for (auto& n : (*G).get_nodes()) {
		if ((*n).get_color()) {
			DFS_tree.add_node(n);
			DFS_visit(&DFS_tree , n);
		}
	}
	(*G).reset_node_colors();
	return DFS_tree;
}





///////////////////////////////////////////////////////////////////////
//  BFS 
///////////////////////////////////////////////////////////////////////


// Bredth first seach 
//		retruns a tree graph from BFS 
Graph BFS(Graph* G, Node* start) {
	Graph BFS_tree;
	if (!(*G).is_node_in_graph(start)) {
		std::cout << "This start node isn't even in the graph" << std::endl;
		return BFS_tree;
	};
	std::queue<Node*> q; 
	q.push(start);
	Node* u;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (auto& v : (*u).get_out_neighbors()) {
			if ((*v).get_color()) {
				(*v).set_color(false);
				q.push(v);
				BFS_tree.add_edge(u, v);
			}
		}
	}
	return BFS_tree;
}







///////////////////////////////////////////////////////////////////////
//  Dijkstra's 
///////////////////////////////////////////////////////////////////////



