#pragma once
#include<stdio.h>
#include<random>


class RndCreate
{
private:
using mt19937_64 = std::mt19937_64;
using random_device = std::random_device;

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
	double getRandDouble(double i, double j)
	{
		std::uniform_real_distribution<> floatRand(i, j);
		return floatRand(mt);
	}

	float getRandFloat(float i, float j)
	{
		std::uniform_real_distribution<> floatRand(i, j);
		
		return (float)floatRand(mt);
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
	static float sGetRandFloat(double i, double j)
	{
		std::mt19937_64 mt;
		std::random_device rnd;
		mt.seed(rnd());
		mt.seed(rnd());
		std::uniform_real_distribution<> floatRand(i, j);
		return (float)floatRand(mt);
	}
private:

	mt19937_64 mt;
	random_device rnd;
};

