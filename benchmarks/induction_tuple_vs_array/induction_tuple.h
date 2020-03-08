
#include <functional>
#include <tuple>
#include "../lattice.h"

/* implements forwards and backwards induction on a lattice */
const int laticeNomial_array = 2;//binomial

template<typename T>
void forwardInduction(T rootVal, Lattice<T, laticeNomial_array>& lattice, 
					const std::function<std::tuple<T, T>(T)>& gen)
{
	lattice[0][0] = rootVal;
	for(size_t i = 0; i < lattice.size() - 1; i++){
		for(size_t j = 0; j < lattice[i].size(); j++){
			std::tie(lattice[i+1][j], lattice[i+1][j+1]) = gen(lattice[i][j]);
		}
	}
}

template<typename T>
T backwardsInduction(Lattice<T, laticeNomial_array>& lattice, 
					const std::function<T(std::tuple<T, T>, T)>& backGen,
					const std::function<T(T)>& leafGen,
					const std::function<T(T,T)>& adjust)
{
	for(size_t j = 0; j < lattice[lattice.maxIndex()].size(); j++){
		lattice[lattice.maxIndex()][j] = leafGen(lattice[lattice.maxIndex()][j]);
	}
	
	for(long i = lattice.maxIndex() - 1; i >= 0; i--){
		for(long j = 0; j < lattice[i].size(); j++){
			std::tuple<T, T> t{lattice[i+1][j], lattice[i+1][j+1]};
			T latticeVal = lattice[i][j];
			lattice[i][j] = backGen(t, lattice[i][j]);
			lattice[i][j] = adjust(latticeVal, lattice[i][j]);
		}
	}
	
	return lattice[0][0];
}
