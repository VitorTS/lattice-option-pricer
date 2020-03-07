/* STL friendly Lattice ADT */

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
	
	std::vector<Node>& operator [] (const int i);
	
	using iterator = typename std::vector<std::vector<Node>>::const_iterator;
	
	iterator begin() const;
	
	iterator end() const;
	
	std::size_t size() const;
	
	std::size_t maxIndex() const;
	
};

#include "lattice.cpp"

#endif