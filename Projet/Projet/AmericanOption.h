#pragma once
#include "Option.h"

class AmericanOption :public Option
{
private:
	double _American_Strike; 
public:
	AmericanOption(double, double); 
	bool isAmericanOption() override; 
	double GetStrike(); 
};

