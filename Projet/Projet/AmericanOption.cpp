#include "AmericanOption.h"


AmericanOption::AmericanOption(double expi, double Strike) : 
	Option(expi), _American_Strike(Strike) {
}


bool AmericanOption::isAmericanOption() { 
	return true;
}


double AmericanOption::GetStrike() {
	return _American_Strike;
}
