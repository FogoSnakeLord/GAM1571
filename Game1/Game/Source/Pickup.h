#pragma once
#include "GameObject.h"
class Pickup: public GameObject
{
public:
	Pickup(std::vector<float> v, int nV);
	~Pickup();
	void Deactivate();
	bool GetIsActive();
protected:
	bool m_IsActive;
};

