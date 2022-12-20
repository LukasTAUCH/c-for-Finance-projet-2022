#include "MT.h"
#include <iostream>
#include <random>

MT MT::Mersene_generator;


MT::MT() : generator(std::random_device()()) 
{
	
}

MT& MT::getInstance() 
{
	return Mersene_generator;
}


std::mt19937& MT::getGenerator() 
{
	return Mersene_generator.generator;
}


MT::~MT() 
{
	
}


double MT::rand_unif()
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	double number = distribution(MT::getGenerator());
	return number;
}
double MT::rand_norm()
{

	std::normal_distribution<double> distribution(0.0, 1.0);
	double number = distribution(MT::getGenerator());
	return number;
}
