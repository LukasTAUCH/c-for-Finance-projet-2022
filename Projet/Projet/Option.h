#pragma once
#include "vector"


class Option
{
public: 
	Option();
	Option(double);
	double getExpiry();

	virtual double payoff(double SN) = 0;
	virtual double payoffPath(std::vector<double>);
	virtual bool isAsianOption();
	virtual bool isAmericanOption();

	~Option();
	friend class CRRPricer;
	friend class BlackScholesMCPricer;

	//double payoff(std::vector<double> S);

private : 
	double _expiry;
};

	


