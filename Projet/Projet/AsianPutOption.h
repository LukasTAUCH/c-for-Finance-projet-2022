#pragma once
#include <vector>
#include "AsianOption.h"

class AsianPutOption : public AsianOption
{
public:
	AsianPutOption(std::vector<double>, double); 
	double payoff(double) override; 
private:
	double _Asian_Strike_Put; 
};

