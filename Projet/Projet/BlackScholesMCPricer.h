#pragma once
#include "Option.h"
class BlackScholesMCPricer
{
private:
	long generated_paths; 
	Option* option;
	double initial_price;
	double interest_rate;
	double volatility;
	double price;
public:
	BlackScholesMCPricer(Option*, double, double, double);
	long getNbPaths();
	double generate(int);
	double operator()();
	std::vector<double> confidenceInterval(); // interval at 95% of the estimate 
};


