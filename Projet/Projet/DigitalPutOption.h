#pragma once
#include "DigitalOption.h"

class DigitalPutOption : public DigitalOption
{
public:
	DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) {}
	~DigitalPutOption() {};
	optionType GetOptionType2() override
	{
		return optionType::put;
	}
	double payoff(double z) override
	{
		double k = GetStrikeDigital();
		double put_payoff = 0;
		if (z <= k) {
			put_payoff = 1;
		}
		else
		{
			put_payoff = 0;
		}
		return put_payoff;
	}
};

