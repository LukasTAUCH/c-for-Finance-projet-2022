#include "AsianOption.h"
#include <vector>



AsianOption::AsianOption(std::vector<double> timesVector) : Times(timesVector) 
{

};


std::vector<double> AsianOption::getTimeSteps() 
{ 
	return Times;
}


bool AsianOption::isAsianOption() 
{ 
	return true;
}

double AsianOption::payoffPath(std::vector<double> sousjacent)
{ 
	double sum = 0;
	for (int k = 0; k < getTimeSteps().size(); k++) {
		sum = sum + sousjacent[k];
	}
	return payoff((1.0 / getTimeSteps().size()) * sum);
}

