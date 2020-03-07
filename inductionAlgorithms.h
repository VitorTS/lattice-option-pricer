#include<cmath>
#include <algorithm>
#include <functional>
#include<tuple>
#include "option_type.h"

/* function object with lattice algorithms */

//trigeorgis
class TRGLatticeInductor{
private:
	double u, d, pudisc, pddisc;
public:
	TRGLatticeInductor(OptionData data){
		double v = data.r - data.sig*data.sig*0.5;
		double dt = data.T / data.N;
		
		double dxu = sqrt((data.sig*data.sig)*dt + (v*v)*(dt*dt));
		double dxd = -dxu;
		
		double pu = 0.5 + 0.5*((v*dt)/dxu);
		double pd = 1 - pu;
		
		//precompute variables 
		u = std::exp(dxu - dxd);
		d = std::exp(dxd);
		
		double disc = std::exp(-data.r * dt);
		pudisc = pu * disc;
		pddisc = pd * disc;
	};
	
	//forwards
	std::tuple<double, double> operator() (double assetPrice){
		return std::make_tuple<double, double>(assetPrice  * u, assetPrice  * d);
	};
	
	//backwards
	double operator() (std::tuple<double, double> upDown, double assetPrice){
		return std::get<0>(upDown) * pudisc + std::get<1>(upDown) * pddisc;
	};
};
