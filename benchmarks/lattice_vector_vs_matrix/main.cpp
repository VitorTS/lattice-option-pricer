#include <cmath>
#include <algorithm>
#include <iostream>
#include "lattice_vector.h"
#include "lattice_matrix.h"
#include "induction_vector.h"
#include "induction_matrix.h"
#include "../../inductionAlgorithms.h"
#include "../../benchmark.h"

int main()
{
	Benchmark<> bench{};
	bench.start();
	
	OptionData option;
	option.K = 100.0;
	option.S = 100.0;
	option.T = 1.0;
	option.r = 0.06;
	option.q = 0.0;
	option.sig = 0.2;
	option.H = 95;
	option.N = 3;
	
	auto plainOptionPrice = [&option](double assetPrice){
		return std::max(option.K - assetPrice, 0.0);
	};
	
	auto earlyExercise = [&plainOptionPrice](double assetPrice, double optionPrice){
		return std::max(plainOptionPrice(assetPrice), optionPrice);
	};
	
	//compares induction algorithm with std::tuple vs std::array
	double benchResult;
	
	for(int i = 0; i < 1'000'000; i++){
		TRGLatticeInductor algorithm(option);
		Lattice_vector<double, 2> lattice{option.N};
		
		forwardInduction<double>(option.S, lattice, algorithm);
		double optionPrice = backwardsInduction<double>(lattice, algorithm, plainOptionPrice, earlyExercise);
	}
	
	benchResult = bench.stop();
	std::cout << "Pricing with std::vector took " << benchResult << " milliseconds" << '\n';
	
	
	bench.start();
	
	for(int i = 0; i < 1'000'000; i++){
		TRGLatticeInductor algorithm(option);
		Lattice_matrix<double, 2> lattice2{option.N};
		
		forwardInduction<double>(option.S, lattice2, algorithm);
		double optionPrice = backwardsInduction<double>(lattice2, algorithm, plainOptionPrice, earlyExercise);
	}
	benchResult = bench.stop();
	std::cout << "Pricing with ublas::matrix took " << benchResult << " milliseconds" << '\n';
	
	return 0;
}