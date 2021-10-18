#pragma once
#include <random>

class Random
{
public:
	Random();
	~Random();
	int RandInt(int min, int max);
	float RandFloat(int min, int max);

protected:
	std::mt19937 m_MiddleVariable;
};