#pragma once
#include "Option.h"

class DigitalOption : public Option
{
public:
	enum class optionType { call, put };
	DigitalOption(double expiry, double strike): Option(expiry), _Strike_Digital(strike) {}
	~DigitalOption() {};
	double GetStrikeDigital();
	virtual optionType GetOptionType2() = 0;
	friend class BlackScholesPricer;

private: 
	double _Strike_Digital;
};



