#include "Option.h"

Option::Option():_expiry(0.0) {}

Option::Option(double expi)
{
	_expiry = expi;
}

double Option::getExpiry()
{
	return _expiry;
};

bool Option::isAsianOption() {
	return false;
}

bool Option::isAmericanOption() {
	return false;
}

Option::~Option()
{

}

double Option::payoffPath(std::vector<double> vect) 
{
	return payoff(vect.back());
}

