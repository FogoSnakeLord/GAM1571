#include "Random.h"

Random::Random():
	m_MiddleVariable(std::random_device{}())
{
}

Random::~Random()
{
}

int Random::RandInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(m_MiddleVariable);
}

float Random::RandFloat(int min, int max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(m_MiddleVariable);
}
