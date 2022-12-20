#pragma once
#include "Option.h"


class VanillaOption :  public Option
{
public: 
	VanillaOption(double expiry, double strike);
	double getStrike();
	enum class optionType { call, put };
	virtual optionType GetOptionType() = 0;
	~VanillaOption() {};
	friend class BlackScholesPricer;

private:
	double _strike;
	
};



