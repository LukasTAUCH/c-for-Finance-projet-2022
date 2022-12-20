#include "AsianPutOption.h"
#include "AsianOption.h"
#include <vector>

AsianPutOption::AsianPutOption(std::vector<double> timesVector, double Strike) : AsianOption(timesVector), _Asian_Strike_Put(Strike) {} //constructor

double AsianPutOption::payoff(double sumsousjacent)
{ 
	double payoff = 0;
	payoff = _Asian_Strike_Put - sumsousjacent;
	if (payoff <= 0) { payoff = 0; }
	return payoff;
}