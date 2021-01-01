

#include "Algorithms.h"


// Unweighted
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




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
void DFS_visit(Graph* G, std::vector<Node*>* parents, Node* u) {
	//std::cout << " DFS visiting node : " << (*u).get_val() << std::endl;
	(*u).set_color(false);
	for (auto& v : (*u).get_out_neighbors()) {
		if( (*v).get_color() ){
			(*parents)[get_index( (*G).get_nodes() , v )] = u;
			DFS_visit(G, parents, v);
		}
	}
};


// main call to run depth first search
//		should probably return PARENT RELATIONS... std::vector<Node*>
std::vector<Node*> DFS(Graph* G) {
	std::vector<Node*> parents((*G).get_nodes().size());
	for (auto& n : (*G).get_nodes()) {
		if ((*n).get_color()) {
			DFS_visit(G, &parents, n);
		}
	}
	(*G).reset_node_colors();
	return parents;
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






// Weighted
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//  Prim's 
///////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////
//  Kruskal's 
///////////////////////////////////////////////////////////////////////
//WeightedGraph Kruskal_MST(WeightedGraph* G) {}




///////////////////////////////////////////////////////////////////////
//  Dijkstra's 
///////////////////////////////////////////////////////////////////////

//typedef std::pair<Node*, unsigned int> NodeEdgePair; // https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/ had to check this out to fix my min heap ... RIP 

std::map<Node*, unsigned int> Dijkstras(WeightedGraph<unsigned int>* G, Node* source) {
	// initialize 
	std::map<Node*, unsigned int> shortest_path_length;
	std::map<Node*, Node*> parent;
	std::set<Node*> s; // set of all nodes NOT checked
	for (auto& n : (*G).get_nodes()) {
		shortest_path_length[n] = 1e6;
		parent[n] = nullptr;
	}
	shortest_path_length[source] = 0; // shortest path from the source to itself is 0 	 
	std::priority_queue< NodeEdgePair, std::vector <NodeEdgePair>, std::greater<NodeEdgePair> > min_heap;
	min_heap.push(std::make_pair(source, 0));

	while (!min_heap.empty()) {
		Node* u = min_heap.top().first; // extract the min 
		min_heap.pop();
		s.erase(u);
		for (auto& v : (*u).get_out_neighbors()) {
			// relax u, v, w
			unsigned int w = G->get_edge_weight(u, v);
			if ( shortest_path_length[v] > shortest_path_length[u] + w ) {
				shortest_path_length[v] = shortest_path_length[u] + w;
				parent[v] = u;
				min_heap.push(std::make_pair(v, shortest_path_length[u] + w));
			}
		}
	}


	return shortest_path_length;
}



