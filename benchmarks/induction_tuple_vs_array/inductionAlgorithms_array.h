#include<cmath>
#include<algorithm>
#include<functional>
#include<array>
#include "../option_type.h"

/* function object with lattice algorithms */

//trigeorgis
class TRGLatticeInductor_array{
private:
	double u, d, pudisc, pddisc;
public:
	TRGLatticeInductor_array(OptionData data){
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
	std::array<double, 2> operator() (double assetPrice){
		return std::array<double, 2>{assetPrice * u, assetPrice * d};
	};
	
	//backwards
	double operator() (std::array<double, 2> upDown, double assetPrice){
		return upDown[0] * pudisc + upDown[1] * pddisc;
	};
};
