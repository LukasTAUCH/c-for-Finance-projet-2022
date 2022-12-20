#pragma once
#include <vector>
#include "Option.h"

class AsianOption :public Option
{
public:
	AsianOption(std::vector<double>);   
	std::vector<double> getTimeSteps();
	bool isAsianOption() override;
	double payoffPath(std::vector<double>) override; 
private:
	std::vector<double> Times; 
};

