#pragma once
#include "GameObject.h"
class GameObjectPool
{
public:
	GameObjectPool();
	~GameObjectPool();
	void ReturnToPool(GameObject*);
	GameObject* GetGameObject();
protected:
	std::vector <GameObject*> m_Pool;
};

