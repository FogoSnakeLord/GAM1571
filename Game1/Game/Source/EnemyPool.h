#pragma once
#include "GameObjectPool.h"
#include "Enemy.h"
class EnemyPool: public GameObjectPool
{
public:
	EnemyPool();
	~EnemyPool();
	Enemy* GetEnemy(int dir);
protected:

};

