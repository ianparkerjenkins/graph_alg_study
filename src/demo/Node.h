#pragma once

// node class 

#include <vector>
#include <iostream>

class Node {

public:

	// constructors
	Node() {};
	Node(double val_) : val(val_) {};



	// setters
	void set_val(double val_) { val = val_; };

	void set_color(bool color_) { color = color_; };

	void add_in_neighbor(Node* in) { 
		in_neighbors.push_back(in);
	};

	void add_out_neighbor(Node* out) { 
		out_neighbors.push_back(out);
	};
		


	// getters
	double get_val() { 
		return val;
	};

	int get_color() {
		return color;
	};

	std::vector<Node*> get_in_neighbors() {
		return in_neighbors;
	};

	std::vector<Node*> get_out_neighbors() {
		return out_neighbors;
	};;
			   


private: 
	double val{ 0 };
	bool color{ true }; // used to determine if it's been visited
	std::vector<Node*> in_neighbors;
	std::vector<Node*> out_neighbors;

};