#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <tuple>
#include <iostream>

template<typename Node, int nomial>
class Lattice{
	static_assert((nomial != 2 || nomial != 3), "Lattice type can only be binomial (2) or trinomial (3)");
private:
	std::vector<std::vector<Node>> tree;
public:
	Lattice(const int N);
	
	int size1() const{
		return tree.size();
	};
	
	int size2() const{
		return tree.end().size();
	};
	
	int maxIndex() const{
		return tree.size() - 1;
	};
	
	Node& operator() (int m, int n){
		return tree[m][n];
	}
};

#include "lattice.cpp"

#endif