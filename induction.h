#include "lattice.h"

const int laticeNomial = 2;//binomial

template<typename T>
void forwardInduction(T rootVal, Lattice<T, laticeNomial>& lattice, 
					std::function<std::tuple<T, T>(T)> gen)
{
	lattice[0][0] = rootVal;
	for(size_t i = 0; i < lattice.size() - 1; i++){
		for(size_t j = 0; j < lattice[i].size(); j++){
			std::tie(lattice[i+1][j], lattice[i+1][j+1]) = gen(lattice[i][j]);
		}
	}
}

template<typename T>
T backwardsInduction(Lattice<T, laticeNomial>& lattice, 
					std::function<T(std::tuple<T, T>, T)> backGen,
					std::function<T(T)> leafGen)
{
	for(size_t j = 0; j < lattice[lattice.maxIndex()].size(); j++){
		lattice[lattice.maxIndex()][j] = leafGen(lattice[lattice.maxIndex()][j]);
	}
	
	for(long i = lattice.maxIndex() - 1; i >= 0; i--){
		for(long j = 0; j < lattice[i].size(); j++){
			std::tuple<T, T> t{lattice[i+1][j], lattice[i+1][j+1]};
			lattice[i][j] = backGen(t, lattice[i][j]);
		}
	}
	
	return lattice[0][0];
}
