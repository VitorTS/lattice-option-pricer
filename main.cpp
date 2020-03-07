#include <cmath>
#include <algorithm>
#include <iostream>
#include "induction.h"
#include "lattice.h"
#include "inductionAlgorithms.h"
#include "benchmark.h"

int main()
{
	Benchmark<> bench{};
	bench.start();
	
	for(int i = 0; i < 1'000'000; i++){
		OptionData option;
		option.K = 100.0;
		option.S = 100.0;
		option.T = 1.0;
		option.r = 0.06;
		option.q = 0.0;
		option.sig = 0.2;
		option.H = 95;
		option.N = 3;
		
		TRGLatticeInductor algorithm(option);
		Lattice<double, 2> lattice{option.N};
		
		forwardInduction<double>(option.S, lattice, algorithm);
		
		//std::cout << "Asset lattice:" << lattice << std::endl;
		
		auto plainOptionPrice = [&option](double assetPrice){
			return std::max(option.K - assetPrice, 0.0);
		};
		
		auto earlyExercise = [&plainOptionPrice](double assetPrice, double optionPrice){
			return std::max(plainOptionPrice(assetPrice), optionPrice);
		};
		
		double optionPrice = backwardsInduction<double>(lattice, algorithm, plainOptionPrice, earlyExercise);

		//std::cout << "Option price:" << optionPrice << std::endl;
	}
	double result = bench.stop();
	std::cout << "Pricing took " << result << " milliseconds" << '\n';
	
	return 0;
}