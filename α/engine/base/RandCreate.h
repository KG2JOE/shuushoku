#pragma once
#include<stdio.h>
#include<random>

class RndCreate
{
public:
	void Ins()
	{
		mt.seed(rnd());
	}
	int getRandInt(int i, int j)
	{
		//std::mt19937_64 mt(rnd());
		std::uniform_int_distribution<> intRand(i, j);
		//std::uniform_int_distribution<>::param_type param(i, j);
		//intRand.param(param);
		//intRand(i, j);
		return intRand(mt);
	}
	double getRandFloat(double i, double j)
	{
		std::uniform_real_distribution<> floatRand(i, j);
		return floatRand(mt);
	}

	static int sGetRandInt(int i, int j)
	{
		std::mt19937_64 mt;
		std::random_device rnd;
		mt.seed(rnd());
		//std::mt19937_64 mt(rnd());
		std::uniform_int_distribution<> intRand(i, j);
		//std::uniform_int_distribution<>::param_type param(i, j);
		//intRand.param(param);
		//intRand(i, j);
		return intRand(mt);
	}
	static double sGetRandFloat(double i, double j)
	{
		std::mt19937_64 mt;
		std::random_device rnd;
		mt.seed(rnd());
		mt.seed(rnd());
		std::uniform_real_distribution<> floatRand(i, j);
		return floatRand(mt);
	}
private:

	std::mt19937_64 mt;
	std::random_device rnd;
};