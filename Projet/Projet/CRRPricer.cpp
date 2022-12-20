#include "CRRPricer.h"
#include "BinaryTree.h"
#include "iostream"
#include <vector>

/*Définition des fonction de la classe CRRPricer*/

CRRPricer::CRRPricer(Option* option1, int depth, double asset_price, double up, double down, double interest_rate) : _option(option1), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate)
{
	/*
	_option = option1;
	this->_depth = depth;
	this->_asset_price = asset_price;
	this->_up = up;
	this->_down = down;
	this->_interest_rate = interest_rate;
	*/
	arbitrage = true;
	if ((up > interest_rate) && (interest_rate > down))
	{
		arbitrage = false;
		std::cout << "Arbitrage false: " << arbitrage << std::endl;
	}

	if (_option->isAsianOption() || _option->isAmericanOption())
	{
		throw std::invalid_argument("It's an Asian Option or American Option so can't use this constructor ! But for an AmericanOption you can use the other constructor with volatility !");
	}
};

CRRPricer::CRRPricer(Option* _op, int depth, double asset_price, double r, double volatility) : _option(_op), _depth(depth), _asset_price(asset_price), _interest_rate(r), volatility(volatility) {

	if (_option->isAsianOption())
	{
		throw std::invalid_argument("Asian Option... Can't use the CRR pricer.");
	}
	else
	{
		double h = double(_option->getExpiry()) / double(depth);
		double A = (_interest_rate + ((double(volatility) * double(volatility)) / double(2)));
		double BU = (h + volatility * sqrt(h));
		double BD = (h - volatility * sqrt(h));
		_up = exp(A * BU) - 1;
		_down = exp(A * BD) - 1;
		_interest_rate = exp(_interest_rate * h) - 1;
	}
}






// NOUS SERT A RIEN
int coefBinomial(int n, int k)
{
	if (k > (n - k))
		k = n - k;

	int coef = 1;

	/*
		Calculer la valeur de [n * (n-1) --- (n-k + 1)]
		/ [k * (k-1) ---- 1]
	*/
	for (int i = 0; i < k; i++) {
		coef *= (n - i);
		coef /= (i + 1);
	}

	return coef;
}


double CRRPricer::get(int depth, int index)
{
	return CRRPricer::_treeCR.getNode(depth, index);
}

//CHANGER CERTAINES NOM VARIABLES


void CRRPricer::compute()
{
	double q = double(_interest_rate - _down) / double(_up - _down);

	CRRPricer::_treeCR.setDepth(_depth);

	for (int j = 0; j <= CRRPricer::_treeCR._depth; j++) {
		double Sn = _asset_price * pow((1 + _up), j) * pow((1 + _down), CRRPricer::_treeCR._depth - j);

		CRRPricer::_treeCR.setNode(CRRPricer::_treeCR._depth, j, _option->payoff(Sn));

	}


	for (int n = CRRPricer::_treeCR._depth - 1; n >= 0; n--)
	{

		if (_option->isAmericanOption() == true) {
			
			for (int i = n; i >= 0; i--) {
				double value = q * CRRPricer::_treeCR.getNode(n + 1, i + 1) + (1 - q) * CRRPricer::_treeCR.getNode(n + 1, i);
				double Hn = value / (1 + _interest_rate);
				double value_2 = get(n, i);
				if (value <= value_2) {
					Hn = value_2;
				}
				CRRPricer::_treeCR.setNode(n, i, Hn);
			}
		}

		else 
		{
			for (int i = n; i >= 0; i--) {
				double value = q * CRRPricer::_treeCR.getNode(n + 1, i + 1) + (1 - q) * CRRPricer::_treeCR.getNode(n + 1, i);
				double Hn = value / (1 + _interest_rate);
				//std::cout << "debut get" << std::endl;
				//std::cout << CRRPricer::_tree.getNode(n + 1, i + 1) << " et " << CRRPricer::_tree.getNode(n + 1, i) << std::endl;
				CRRPricer::_treeCR.setNode(n, i, Hn);
			}
		}
	}
}

bool CRRPricer::getExercice(int n, int i)
{
	bool res = false;
	if (_option->isAmericanOption() == true)
	{
		double payoff_continu = 0;
		double payoff_intrinsic = 0;
		double q = (_interest_rate - _down) / (_up - _down);
		compute();
		payoff_continu = q * CRRPricer::_treeCR.getNode(n + 1, i + 1) + (1 - q) * CRRPricer::_treeCR.getNode(n + 1, i);
		payoff_intrinsic = get(n, i);
		if (payoff_continu <= payoff_intrinsic) {
			res = true;
		}
	}
	else
	{
		std::cout << "Can only be used with american option" << std::endl;
	}
	return res;

}

/*
void CRRPricer::compute()
{

	double S0 = _asset_price;
	double U = _up;
	double D = _down;
	double R = _interest_rate;
	int profondeur = _depth;
	double positif = (1 + U);
	double negatif = (1 + D);
	double q = (R - D) / (U - D);

	//std::vector<std::vector<double>> vecteurarbrebinomial;
	std::vector<double> arbrefor;

	for (int i = 0; i < profondeur + 1; i++) {
		_treeCR.push_back(S0 * pow(positif, profondeur - i) * pow(negatif, i));
		if (K > _tree[i]) {
			arbrefor.push_back(0);
		}
		else {
			arbrefor.push_back(K - _treeCR[i]);
		}
	}
	int Nbr = arbrefor.size(); //nombre d'élements
	while (j < profondeur) {
		alpha = alpha + coefBinomial(profondeur - 1, j) * arbrefor[j] * pow(q, profondeur - (j + 1)) * pow(1 - q, j);
		Beta = Beta + coefBinomial(profondeur - 1, j) * arbrefor[Nbr - (j + 1)] * pow(1 - q, profondeur - (j + 1)) * pow(q, j);
		j++;
	};
	finalprice = (q * alpha + (1 - q) * Beta) / (pow(1 + R, profondeur + 1));

}
*/

/*
void CRRPricer::compute()
{
	std::vector<double> StockPrice;
	double So = _asset_price;
	double U = _up;
	double D = _down;
	double depth = _depth;

	for (int i = 0; i < depth; i++)
	{
		StockPrice[i] = So * pow(1 + U, i) * pow(1 + D, depth - i);
	}



	// truc du bot
	for (int n = depth_; n >= 0; n--) {
		for (int i = 0; i <= n; i++) {
			double S = asset_price_ * pow(up_, i) * pow(down_, n - i);
			tree_(n, i) = (*option_)(S);
		}
	}

	for (int n = depth_ - 1; n >= 0; n--) {
		for (int i = 0; i <= n; i++) {
			tree_(n, i) =
				(tree_(n + 1, i) * (1.0 - interest_rate_) + tree_(n + 1, i + 1) * interest_rate_) /
				(1.0 + interest_rate_);
		}
	}



}
*/


double CRRPricer::operator()(bool closed_form = false)
{
	compute();
	double price = 0;
	double q = (_interest_rate - _down) / (_up - _down);
	_depth = CRRPricer::_treeCR._depth - 1;
	if (closed_form == true) {
		double cst = 1 / pow((1 + _interest_rate), _depth);
		double sum = 0;
		double combi_stock = 1;
		double combi = 0;
		for (int i = 0; i <= _depth; i++) {
			if (i == 0) {
				combi = 1;
			}
			else {
				combi = combi_stock * (double(_depth - (i - 1)) / double(i));
				combi_stock = combi;
			}
			double bino = pow(q, i) * pow(1 - q, _depth - i) * get(_depth, i);
			sum = sum + combi * bino;
		}
		price = sum * cst;
	}
	return price;
}


double CRRPricer::operator()() {
	compute();
	double res = 0;
	double q = (_interest_rate - _down) / (_up - _down);
	_depth = CRRPricer::_treeCR._depth;
	res = get(0, 0);
	return res;
}