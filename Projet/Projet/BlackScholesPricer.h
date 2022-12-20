#pragma once
#include "Option.h"
#include "VanillaOption.h"
#include "DigitalOption.h"


class BlackScholesPricer {
protected:
	VanillaOption* V_option;
	DigitalOption* D_option;
	double asset_price;
	double interest_rate;
	double volatility;
public:
	BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility);
	BlackScholesPricer(DigitalOption*, double, double, double);
	~BlackScholesPricer() {};
	double operator()();
	double delta();
};

