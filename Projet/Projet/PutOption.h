#pragma once
#include "VanillaOption.h"

class PutOption :public VanillaOption {
public:
	PutOption(double put_expir, double put_strike) : VanillaOption(put_expir, put_strike) {};
	~PutOption() {};
	optionType GetOptionType() override
	{
		return optionType::put;
	}
	double payoff(double sousjacent) override
	{
		double k = getStrike();
		double put_payoff = 0;
		if (sousjacent >= k) {
			put_payoff = sousjacent - k;
		}
		else 
		{
			put_payoff = 0;
		}
		return put_payoff;

	}
};

