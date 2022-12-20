#pragma once
#include <random>
#include <iostream>
using namespace std;

class MT
{
public:
	MT(const MT&) = delete;
	MT& operator=(const MT&) = delete;
	MT(MT&) = delete;

	static MT& getInstance();
	static std::mt19937& getGenerator();
	static double rand_unif(); // uniform law
	static double rand_norm(); // normal law
private:
	MT();
	~MT(); 
	mt19937 generator;
	static MT Mersene_generator; 
};
