#ifndef LATTICE_MATRIX_H
#define LATTICE_MATRIX_H

#include <boost/numeric/ublas/triangular.hpp>
namespace ublas = boost::numeric::ublas;

template<typename Node, int nomial>
class Lattice_matrix{
	static_assert((nomial != 2 || nomial != 3), "Lattice type can only be binomial (2) or trinomial (3)");
private:
	ublas::triangular_matrix<Node, ublas::lower> tree;
public:
	Lattice_matrix(const int N): tree(N, N) {};
	
	Node& operator() (const Node m, const Node n){
		return tree(m, n);
	};
	
	std::size_t size1() const{
		return tree.size1();
	}
	
	std::size_t size2() const{
		return tree.size2();
	}
	
	int maxIndex() const{
		return tree.size2() - 1;
	}
};

#include "lattice_matrix.cpp"

#endif
