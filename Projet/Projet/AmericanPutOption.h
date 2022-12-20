#pragma once
#include "AmericanOption.h"



class AmericanPutOption :public AmericanOption
{
public:
	AmericanPutOption(double, double); 
	double payoff(double) override;  
};

