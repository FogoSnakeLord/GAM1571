#pragma once
#include "GameObject.h"
class Pickup: public GameObject
{
public:
	Pickup();
	~Pickup();
	void Deactivate();
	bool GetIsActive();
	void Init();
protected:
	bool m_IsActive;
};

