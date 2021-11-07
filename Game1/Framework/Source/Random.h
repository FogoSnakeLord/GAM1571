#pragma once
#include <random>

class Random
{
public:
	Random();
	~Random();
	int RandInt(int min, int max);
	float RandFloat(float min, float max);

protected:
	std::mt19937 m_MiddleVariable;
};