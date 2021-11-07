#include "GameObjectPool.h"

GameObjectPool::GameObjectPool()
{
}

GameObjectPool::~GameObjectPool()
{
	//for (int i = 0; i < m_Pool.size(); i++) {
	//	delete m_Pool[i];
	//}
	m_Pool.clear();
}

void GameObjectPool::ReturnToPool(GameObject* temp)
{
	m_Pool.push_back(temp);
}

