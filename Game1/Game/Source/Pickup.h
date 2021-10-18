#pragma once
#include "GameObject.h"
class Pickup: public GameObject
{
public:
	Pickup(std::vector<float> v, int nV);
	~Pickup();

protected:
};

