#pragma once
#include "GameObject.h"
class Bullet: public GameObject
{
public:
	Bullet(vec2 dir, vec2 position);
	~Bullet();
	void Init(vec2 dir, vec2 position);
	void Update(float deltaTime);
protected:
	vec2 m_Dir;
};

