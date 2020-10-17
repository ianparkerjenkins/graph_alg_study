#pragma once

#include "Graph.h"

// general connectivity 
void search(Node* u);
bool st_connectivity(Graph* G, Node* u, Node* v);

// DFS
void DFS_visit(Graph* DFS_tree, Node* u);
Graph DFS(Graph* G);


// BFS
Graph BFS(Graph* G, Node* start);

// Dijkstra's


