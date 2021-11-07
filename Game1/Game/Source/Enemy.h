#pragma once
#include "GameObject.h"
class Enemy: public GameObject
{
public:
	Enemy(int type);
	~Enemy();
	void Update(float deltaTime);
	void Deactivate();
	bool GetIsActive();
	void Init(int m_Type);
protected:
	bool m_IsActive;
	int m_Type;
	int m_MoveCounter;
};

