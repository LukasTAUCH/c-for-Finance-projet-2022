#include "AsianCallOption.h"
#include "AsianOption.h"
#include <vector>

AsianCallOption::AsianCallOption(std::vector<double>timesVector, double Strike) :AsianOption(timesVector), _Asian_Strike_Call(Strike) {} //constructor

double AsianCallOption::payoff(double sumsousjacent) { 
	double payoff = 0;
	payoff = sumsousjacent - _Asian_Strike_Call;
	if (payoff <= 0) { payoff = 0; }
	return payoff;
}
