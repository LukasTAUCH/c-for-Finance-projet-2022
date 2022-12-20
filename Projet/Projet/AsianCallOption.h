#pragma once
#include <vector>
#include "AsianOption.h"

class AsianCallOption :public AsianOption
{
public:
	AsianCallOption(std::vector<double>, double); 
	double payoff(double) override; 
private:
	double _Asian_Strike_Call; 
};

