#include "BlackScholesPricer.h"
#include "iostream"
#include"string"
#include "math.h"
#include "vector"
#include<list>

/*Définition des fonction de la classe BlackscholesPricer*/

BlackScholesPricer::BlackScholesPricer(VanillaOption* option1, double asset_price, double interest_rate, double volatility) : V_option(option1)
{
	this->D_option = NULL;
	this->asset_price = asset_price;
	this->interest_rate = interest_rate;
	this->volatility = volatility;

}


BlackScholesPricer::BlackScholesPricer(DigitalOption* option2, double asset_price, double interest_rate, double volatility) : D_option(option2)
{
	this ->V_option = NULL;
	this->asset_price = asset_price;
	this->interest_rate = interest_rate;
	this->volatility = volatility;

}




double N(double x) 
{
	return 0.5 * (2 - erfc(x / sqrt(2.0)));
};


double BlackScholesPricer::operator()() {
	//double T = V_option->getExpiry();
	//double T_digital = D_option->getExpiry();
	//double K = V_option->getStrike();
	//double K_digital = D_option->GetStrikeDigital();
	double priceoption = 0;
	double sigmasqarre = volatility * volatility;
	double So = asset_price;
	double R = interest_rate;
	//double d_un = (log(So / K) + (R + sigmasqarre / 2) * T) / (sqrt(sigmasqarre * T));
	//double d_deux = d_un - sqrt(sigmasqarre * T);
	//double d_un_digital = (log(So / K_digital) + (R + sigmasqarre / 2) * T_digital) / (sqrt(sigmasqarre * T_digital));
	//double d_deux_digital = d_un_digital - sqrt(sigmasqarre * T_digital);

	if (V_option == NULL)
	{
		double K_digital = D_option->GetStrikeDigital();
		double T_digital = D_option->getExpiry();

		double d_un_digital = (log(So / K_digital) + (R + sigmasqarre / 2) * T_digital) / (sqrt(sigmasqarre * T_digital));
		double d_deux_digital = d_un_digital - sqrt(sigmasqarre * T_digital);

		if (D_option->GetOptionType2() == DigitalOption::optionType::call)
		{
			priceoption = N(d_un_digital) * So - K_digital * exp(-R * T_digital) * N(d_deux_digital);
		}
		else
		{
			priceoption = N(d_un_digital) * (-So) + K_digital * exp(-R * T_digital) * N(-d_deux_digital);
		}
	}

	else
	{
		double T = V_option->getExpiry();
		double K = V_option->getStrike();
		double d_un = (log(So / K) + (R + sigmasqarre / 2) * T) / (sqrt(sigmasqarre * T));
		double d_deux = d_un - sqrt(sigmasqarre * T);

		if (V_option->GetOptionType() == VanillaOption::optionType::call)
		{
			priceoption = So * N(d_un) - K * exp(-R * T) * N(d_deux);
		}
		else
		{
			priceoption = -So * N(-d_un) + K * exp(-R * T) * N(-d_deux);
		}
	}

	return priceoption;

	/*
	if (V_option == NULL && D_option->GetOptionType2() == DigitalOption::optionType::call)
	{
		priceoption = N(d_un_digital) * So - K_digital * exp(-R * T_digital) * N(d_deux_digital);

	}
	else if (V_option == NULL && D_option->GetOptionType2() == DigitalOption::optionType::put)
	{
		priceoption = N(d_un_digital) * (-So) + K_digital * exp(-R * T_digital) * N(-d_deux_digital);

	}
	
	if (V_option != NULL && V_option->GetOptionType() == VanillaOption::optionType::call) {
		priceoption = So * N(d_un) - K * exp(-R * T) * N(d_deux);
	}
	else if (V_option != NULL && V_option->GetOptionType() == VanillaOption::optionType::put)
	{
		priceoption = -So * N(-d_un) + K * exp(-R * T) * N(-d_deux);
	}

	return priceoption;
	*/
};


double BlackScholesPricer::delta() {

	//double T = V_option->getExpiry();
	//double K = V_option->getStrike();
	//double T_digital = D_option->getExpiry();
	//double K_Digital = D_option->GetStrikeDigital();
	double sigmasqarre = volatility;
	double So = asset_price;
	double R = interest_rate;
	//double d_un = (log(So / K) + (R + sigmasqarre / 2) * T) / (sqrt(sigmasqarre * T));
	//double d_un_Digital = (log(So / K_Digital) + (R + sigmasqarre / 2) * T_digital) / (sqrt(sigmasqarre * T_digital));
	double show = 0;

	
	if (V_option == NULL)
	{
		double T_digital = D_option->getExpiry();
		double K_Digital = D_option->GetStrikeDigital();
		double d_un_Digital = (log(So / K_Digital) + (R + sigmasqarre / 2) * T_digital) / (sqrt(sigmasqarre * T_digital));

		if (D_option->GetOptionType2() == DigitalOption::optionType::call)
		{
			show = N(d_un_Digital);
		}
		else
		{
			show = N(d_un_Digital) - 1;
		}
	}

	else
	{
		double T = V_option->getExpiry();
		double K = V_option->getStrike();
		double d_un = (log(So / K) + (R + sigmasqarre / 2) * T) / (sqrt(sigmasqarre * T));

		if (V_option->GetOptionType() == VanillaOption::optionType::call)
		{
			show = N(d_un);
		}
		else
		{
			show = N(d_un) - 1;
		}
	}

	return show;

	/*
	if (V_option == NULL && D_option->GetOptionType2() == DigitalOption::optionType::call)
	{
		show = N(d_un_Digital);
	}
	else if (V_option == NULL && D_option->GetOptionType2() == DigitalOption::optionType::put)
	{

		show = N(d_un_Digital) - 1;
	}
	

	if (V_option != NULL && V_option->GetOptionType() == VanillaOption::optionType::call)
	{
		show = N(d_un);
	}

	else if (V_option != NULL && V_option->GetOptionType() == VanillaOption::optionType::put)
	{
		show = N(d_un) - 1;
	}
	return show;
	*/
};


