#pragma once
#include "Node.h"


// !!!!!!!!!!!!!!!!!!!1
// OBE
// !!!!!!!!!!!!!!!!!!!1


class WeightedEdge {

public :

	WeightedEdge(Node* from, Node* to, double w_) : parent(from), child(to), weight(w_) {};

	// setters 
	void set_weight(double w_) { weight = w_; };
	void set_parent(Node* p_) { parent = p_; };
	void set_child(Node* c_) { child = c_; };

	// getters 
	double get_weight() { return weight; };
	Node* get_parent() { return parent; };
	Node* get_child() { return child; };

private : 

	double weight{ 0 }; // TODO : Template type the weight
	Node* parent;
	Node* child;

};