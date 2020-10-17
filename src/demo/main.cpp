
#include<iostream>
#include<vector>
//#include "Graph.h"
#include "Algorithms.h"




// test the functionality of nodes
//		should contain a value and a list of in/out neighbors
int test_node() {

	try
	{
		Node n;
		n.set_val(1.1);

		if (n.get_val() != 1.1) { throw 0; }

		Node m = Node::Node(100.0);
		n.add_in_neighbor(&m);
		m.add_out_neighbor(&n);

		double nx = n.get_val();
		double mx = m.get_val();

		if (nx > mx) { throw 1; }

		//std::cout << nx << std::endl;
		//std::cout << mx << std::endl;
		//std::cout << std::endl;

		Node* mm = m.get_out_neighbors().back();
		Node* nn = n.get_in_neighbors().back();

		double nnx = (*mm).get_val();
		double mmx = (*nn).get_val();
		//std::cout << nnx << std::endl;
		//std::cout << mmx << std::endl;

		if (nnx > mmx) { throw 1; }

	}
	catch (int e)
	{
		std::cout << "Node test failed " << e << '\n';
		return 1;
	}

	return 0;
}



// basic directed an undirected graph functionality 
//		adding an edge should change both the neighbors of both nodes involed witht aht  
int test_graph() {

	try 
	{
		Node n = Node::Node(1.0);
		Node m = Node::Node(2.0);
		Graph G;
		G.add_edge(&n, &m);
		//G.draw();
		std::cout << std::endl;

		if (n.get_out_neighbors()[0] != &m) { throw 0; }

		n.~Node();
		m.~Node();
		n = Node::Node(1.0);
		m = Node::Node(2.0);
		UndirectedGraph UG;
		UG.add_edge(&n, &m);
		//UG.draw();
		std::cout << std::endl;
		if (n.get_out_neighbors()[0] != &m) { throw 1; }
		if (n.get_in_neighbors()[0] != &m ) { throw 2; }


		// Dense graph not dense ?? 
		//n.~Node();
		//m.~Node();
		//n = Node::Node(1.0);
		//m = Node::Node(2.0);
		//Node l = Node::Node(3.0);
		//DenseGraph DG;
		//DG.add_node(&n);
		//DG.add_node(&m);
		//DG.add_node(&l);
		//DG.draw();
		//std::cout << " "  << std::endl;
		//std::cout << std::endl;
	}
	catch (int e)
	{
		std::cout << "Basic graph test failed " << e << '\n';
		return 1;
	}

	return 0;
}




// test s-t connectivity algorithm 
//		should return 1 (true) if two
int test_st_con() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);
	Node foo = Node::Node(5.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	G.add_node(&foo);
	//G.draw();
	//std::cout << std::endl;

	//std::cout << st_connectivity(&G, &n, &l) << std::endl;
	//std::cout << st_connectivity(&G, &foo, &l) << std::endl;
	//std::cout << st_connectivity(&G, &l, &foo) << std::endl;

	try
	{
		if (!st_connectivity(&G, &n, &l)) { throw 0; }
		if (st_connectivity(&G, &foo, &l)) { throw 1; }
		if (st_connectivity(&G, &l, &foo)) { throw 2; }
	}
	catch (int e)
	{
		std::cout << "s-t connectivity test failed " << e << '\n';
		return 1;
	}


	return 0;
}


int test_dfs() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);
	Node foo = Node::Node(5.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	G.add_node(&foo);
	//G.draw();

	Graph G_tree = DFS(&G);
	//G_tree.draw();

	int i = 0;

	try
	{
		for (auto& n : G.get_nodes()) {
			if (n != G_tree.get_nodes()[i]) { throw i; }
			i += 1;
		}
	}
	catch (int e)
	{
		std::cout << "The DFS tree should be the same as the originial graph for this test : " << e << std::endl;
	}



	return 0;
}


int test_weighted_graph() {
	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	WeightedGraph WG;
	WeightedEdge e1 = WeightedEdge::WeightedEdge(&n, &m, 10.0);
	WeightedEdge e2 = WeightedEdge::WeightedEdge(&m, &l, 11.0);
	WG.add_edge(&e1);
	WG.add_edge(&e2);
	//WG.draw();

	try
	{
		if ((*WG.get_edges()[0]).get_weight() != 10.0) { throw 0; }
		if ((*WG.get_edges()[1]).get_weight() != 11.0) { throw 1; }
		if (n.get_out_neighbors()[0] != &m) { throw 2; }
		if (m.get_out_neighbors()[0] != &l) { throw 3; }
		if (l.get_in_neighbors()[0] != &m) { throw 4; }

	}
	catch (int e)
	{
		std::cout << "something doesn't seem right with test : " << e << std::endl;
	}

	return 0;
}


int test_bfs() {

	Node n = Node::Node(1.0);
	Node m = Node::Node(2.0);
	Node l = Node::Node(3.0);
	Node o = Node::Node(4.0);

	Graph G;
	G.add_edge(&n, &m);
	G.add_edge(&m, &l);
	G.add_edge(&l, &o);
	//G.draw();

	Graph G_tree = BFS(&G, &n);
	//G_tree.draw();

	int i = 0;

	try
	{
		for (auto& n : G.get_nodes()) {
			if (n != G_tree.get_nodes()[i]) { throw i; }
			i += 1;
		}
	}
	catch (int e)
	{
		std::cout << "The BFS tree should be the same as the originial graph for this test : " << e << std::endl;
	}

	return 0;
}




void demo_dfs() {

};





//  test everything here
//	demo case studies of graph algorithms 
int main() {


	// unit tests 
	int test = 0;
	try
	{
		test += test_node();
		test += test_graph();
		test += test_weighted_graph();
		test += test_st_con();
		test += test_dfs();
		test += test_bfs();

		if (test) { throw test; }
	}
	catch (int e)
	{
		std::cout << "Number of failed tests : " << e << std::endl;
	}

	return 0;

}



