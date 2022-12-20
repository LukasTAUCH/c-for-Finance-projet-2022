#include "VanillaOption.h"

VanillaOption::VanillaOption(double expiry, double strike) : Option(expiry)
{
	_strike = strike;
}

double VanillaOption::getStrike()
{
	return _strike;
};
