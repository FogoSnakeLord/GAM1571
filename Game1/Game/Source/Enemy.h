#pragma once
#include "GameObject.h"
class Enemy: public GameObject
{
public:
	Enemy(std::vector<float> v, int nV);
	~Enemy();
	void Update(float deltaTime);
	void Deactivate();
	bool GetIsActive();
protected:
	bool m_IsActive;
};

