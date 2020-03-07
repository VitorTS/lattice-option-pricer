#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <functional>
#include "induction.h"
#include "lattice.h"



int main()
{
	double K = 100.0;
	double S = 100.0;
	double T = 1.0;
	double r = 0.06;
	double q = 0.0;
	double sig = 0.2;
	int N = 3;
	double H = 95;
	
	double v = r - sig*sig*0.5;
	double dt = T / N;
	
	double dxu = sqrt((sig*sig)*dt + (v*v)*(dt*dt));
	double dxd = -dxu;
	
	double pu = 0.5 + 0.5*((v*dt)/dxu);
	
	double pd = 1 - pu;
	
	double u = std::exp(dxu - dxd);
	double d = std::exp(dxd);
	
	//nomial template param isnt doing anything
	Lattice<double, 2> lattice{N};
	
	auto forwardGen = [u, d](double assetPrice){
		return std::make_tuple<double, double>(assetPrice  * u, assetPrice  * d);
	};
	
	forwardInduction<double>(S, lattice, forwardGen);
	
	std::cout << "Asset lattice:" << lattice << std::endl;
	
	auto plainOptionPrice = [K](double assetPrice){
		return std::max(K - assetPrice, 0.0);
	};
	
	//TODO put backwardsGen/forwardGen in a functor with operator () overloaded
	auto backwardsGen = [pu, pd, r, dt, &plainOptionPrice](std::tuple<double, double> upDown, double assetPrice){
		double earlyPrice = plainOptionPrice(assetPrice);
		double backPrice = std::get<0>(upDown) * pu * std::exp(-r * dt) +
		std::get<1>(upDown) * pd * std::exp(-r * dt);
		return std::max<double>(backPrice, earlyPrice);
	};
	
	double optionPrice = backwardsInduction<double>(lattice, backwardsGen, plainOptionPrice);

	std::cout << "Option price:" << optionPrice << std::endl;
	
	return 0;
}