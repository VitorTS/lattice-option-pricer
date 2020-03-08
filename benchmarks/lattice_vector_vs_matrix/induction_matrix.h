/* implements forwards and backwards induction on a lattice */

#include <functional>
#include <array>
#include "lattice_matrix.h"


const int laticeNomial_m = 2;//binomial

template<typename T>
void forwardInduction(T rootVal, Lattice_matrix<T, laticeNomial_m>& lattice, 
					const std::function<std::array<T, laticeNomial_m>(T)>& gen)
{
	lattice(0, 0) = rootVal;
	
	for(size_t i = 0; i < lattice.maxIndex(); i++){
		for(size_t j = 0; j <= i; j++){
			auto arr = gen(lattice(i, j));
			lattice(i+1, j) = arr[0];
			lattice(i+1, j + 1) = arr[1];
		}
	}
}

template<typename T>
T backwardsInduction(Lattice_matrix<T, laticeNomial_m>& lattice, 
					const std::function<T(std::array<T, laticeNomial_m>, T)>& backGen,
					const std::function<T(T)>& leafGen,
					const std::function<T(T,T)>& adjust)
{
	for(size_t j = 0; j < lattice.size1(); j++){
		lattice(lattice.maxIndex() , j) = leafGen(lattice(lattice.maxIndex() , j));
	}
	
	for(long i = lattice.maxIndex() - 1; i >= 0; i--){
		for(long j = 0; j <= i; j++){
			std::array<T, laticeNomial_m> arr{lattice(i+1, j), lattice(i+1, j + 1)};
			T latticeVal = lattice(i, j);
			lattice(i, j) = backGen(arr, lattice(i, j));
			lattice(i, j) = adjust(latticeVal, lattice(i, j));
		}
	}
	
	return lattice(0,0);
}
