#include "AmericanPutOption.h"
#include "VanillaOption.h"




AmericanPutOption::AmericanPutOption(double expi, double Strike) : AmericanOption(expi, Strike) { } //constructor

double AmericanPutOption::payoff(double z) 
{ 
	double strike = GetStrike();
	double res;
	if (z >= strike) {
		res = z - strike;
	}
	else {
		res = 0;
	}
	return res;
}
