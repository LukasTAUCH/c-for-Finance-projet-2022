#pragma once
#include "Option.h"
#include "BinaryTree.h"


class CRRPricer {

private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    double volatility;

public: 
    BinaryTree<double> _treeCR;
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);
    ~CRRPricer() {};
    void compute();
    double get(int depth, int index);
    bool getExercice(int, int);
    double operator()(bool);
    double operator()();
    bool arbitrage;
    

};
