#pragma once
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption
{
public:
	~DigitalCallOption() {};
	DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike) {}
	optionType GetOptionType2() override
	{
		return optionType::call;
	}
	double payoff(double z)  override
	{
		double k = GetStrikeDigital();
		double put_payoff = 0;
		if (z >= k) {
			put_payoff = 1;
		}
		else
		{
			put_payoff = 0;
		}
		return put_payoff;
	}
};

