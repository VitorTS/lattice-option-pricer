#include <cmath>
#include <algorithm>
#include <iostream>
#include "lattice.h"
#include "induction.h"
#include "inductionAlgorithms.h"
#include "induction_array.h"
#include "inductionAlgorithms_array.h"
#include "benchmark.h"

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
	
	double benchResult;
	
	for(int i = 0; i < 1'000'000; i++){
		TRGLatticeInductor algorithm(option);
		Lattice<double, 2> lattice{option.N};
		
		forwardInduction<double>(option.S, lattice, algorithm);
		
		//std::cout << "Asset lattice:" << lattice << std::endl;
		
		double optionPrice = backwardsInduction<double>(lattice, algorithm, plainOptionPrice, earlyExercise);

		//std::cout << "Option price:" << optionPrice << std::endl;
	}
	
	benchResult = bench.stop();
	std::cout << "Pricing took " << benchResult << " milliseconds" << '\n';
	
	
	bench.start();
	
	for(int i = 0; i < 1'000'000; i++){
		TRGLatticeInductor_array algorithm(option);
		Lattice<double, 2> lattice{option.N};
		
		forwardInduction_array<double>(option.S, lattice, algorithm);
		double optionPrice = backwardsInduction_array<double>(lattice, algorithm, plainOptionPrice, earlyExercise);
	}
	benchResult = bench.stop();
	std::cout << "Pricing took " << benchResult << " milliseconds" << '\n';
	
	return 0;
}