#include <cmath>
#include <algorithm>
#include <iostream>
#include "lattice.h"
#include "option_type.h"
#include "induction.h"
#include "inductionAlgorithms.h"

int main()
{
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
	
	TRGLatticeInductor algorithm(option);

	Lattice<double, 2> lattice{option.N};
	
	for(long i = 0; i < lattice.size1(); i++){
		std::cout << i << '\n';
	}
	
	for(long i = lattice.maxIndex() - 1; i >= 0; i--){
		for(long j = 0; j <= i; j++){
			std::cout << i << ' ' << j << '\n';
		}
	}
	forwardInduction<double>(option.S, lattice, algorithm);
	double optionPrice = backwardsInduction<double>(lattice, algorithm, plainOptionPrice, earlyExercise);
	
	std::cout << lattice << '\n';
	
	std::cout << "option price is " << optionPrice << '\n';
	return 0;
}