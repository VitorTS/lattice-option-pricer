#ifndef LATTICE_VECTOR_H
#define LATTICE_VECTOR_H

#include <vector>
#include <tuple>
#include <iostream>

template<typename Node, int nomial>
class Lattice_vector{
	static_assert((nomial != 2 || nomial != 3), "Lattice type can only be binomial (2) or trinomial (3)");
private:
	std::vector<std::vector<Node>> tree;
public:
	Lattice_vector(const int N);
	
	std::size_t size1() const{
		return tree.size();
	};
	
	std::size_t size2() const{
		return tree.end().size();
	};
	
	int maxIndex() const{
		return tree.size() - 1;
	};
	
	Node& operator() (int m, int n){
		return tree[m][n];
	}
};

#include "lattice_vector.cpp"

#endif