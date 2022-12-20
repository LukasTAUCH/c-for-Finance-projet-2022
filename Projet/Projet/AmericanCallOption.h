#pragma once
#include "AmericanOption.h"

class AmericanCallOption :public AmericanOption
{
public:
	AmericanCallOption(double, double); 
	double payoff(double) override; 
};

