#include "EnemyPool.h"
#include "Random.h"

EnemyPool::EnemyPool()
{
}

EnemyPool::~EnemyPool()
{
}

Enemy* EnemyPool::GetEnemy(int dir)
{
	if (!m_Pool.empty()) {
		Enemy* temp = dynamic_cast <Enemy*> (m_Pool.back());
		m_Pool.pop_back();
		temp->Init(dir);
		return temp;
	}
	else{
		return new Enemy(dir);
	}
}
