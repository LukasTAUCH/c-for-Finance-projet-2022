#include "AmericanCallOption.h"
#include "VanillaOption.h"

AmericanCallOption::AmericanCallOption(double expi, double Strike) : AmericanOption(expi, Strike) { } //constructor

double AmericanCallOption::payoff(double z) 
{ 
	double Strike = GetStrike();
	double res;
	if (z <= Strike) {
		res = Strike - z;
	}
	else {
		res = 0;
	}
	return res;
}

