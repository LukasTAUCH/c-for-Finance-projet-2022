#pragma once
#include "VanillaOption.h"

class CallOption :public VanillaOption {
public:
	CallOption(double call_expir, double call_strike) : VanillaOption(call_expir, call_strike) {};
	~CallOption() {};
	optionType GetOptionType() override
	{
		return optionType::call;
	}

	double payoff(double sousjacent) override
	{
		double k = getStrike();
		double call_payoff = 0;
		if (sousjacent < k) {
			call_payoff = k - sousjacent;
		}
		else 
		{
			call_payoff = 0;
		}
		return call_payoff;		
	}

};


