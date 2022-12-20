#include "BlackScholesMCPricer.h"
#include "MT.h"
#include "AsianOption.h"
#include <vector>
#include <math.h>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : option((Option*)option), initial_price(initial_price), interest_rate(interest_rate), volatility(volatility) {
	generated_paths = 0;
	MT::getInstance();
}


long BlackScholesMCPricer::getNbPaths() {
	return generated_paths;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() {
	double z = 1.96; //Quantile at 97.5% of a normal distribution
	double mu = initial_price;
	double vol_estim = volatility / std::sqrt(generated_paths);
	double lower_bound = mu - z * vol_estim;
	double upper_bound = mu + z * vol_estim;
	std::vector<double> IC;
	IC.push_back(lower_bound);
	IC.push_back(upper_bound);
	return IC;
}

double BlackScholesMCPricer::generate(int nb_paths) 
{
	generated_paths += nb_paths;
	std::vector<double> Zk(nb_paths);
	std::vector<double> Sk(nb_paths);
	std::vector<double> Times(nb_paths);
	if (nb_paths == 0) {
		throw std::invalid_argument("0 added paths");
	}
	if (option->isAsianOption()) 
	{
		Times = ((AsianOption*)option)->getTimeSteps(); 
	}
	else {
		Times[0] = option->getExpiry();
	}
	double res = 0;
	for (int k = 0; k < nb_paths; k++) {
		// Generation of a new path
		for (int i = 0; i < Times.size(); i++) {
			Zk[i] = MT::rand_norm();
			if (i != 0) {
				Sk[i] = Sk[i - 1] * std::exp((interest_rate - (volatility * volatility) / 2) * ((Times[i] - Times[i - 1]) + volatility * std::sqrt(Times[i] - Times[i - 1]) * Zk[i]));

			}
			else {
				Sk[i] = initial_price * std::exp((interest_rate - (volatility * volatility) / 2) * (Times[0] + volatility * std::sqrt(Times[0]) * Zk[0]));
			}
		}
		// Adding the path to the computation of the price
		res += option->payoffPath(Sk);
	}
	res = res * (std::exp(- interest_rate * option->getExpiry()));
	price = ((generated_paths - nb_paths) * price + res) / generated_paths;
	return price;
}

double BlackScholesMCPricer::operator()() {
	if (generated_paths == 0) {
		throw std::invalid_argument("Price not defined "); 
	}
	else 
	{
		return price;
	}
}
