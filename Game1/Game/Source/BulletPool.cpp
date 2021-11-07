#include "BulletPool.h"
#include "Random.h"

BulletPool::BulletPool()
{
}

BulletPool::~BulletPool()
{
}

Bullet* BulletPool::GetBullet(vec2 dir,vec2 position)
{
	if (!m_Pool.empty()) {
		Bullet* temp = dynamic_cast <Bullet*> (m_Pool.back());
		m_Pool.pop_back();
		temp->Init(dir,position);
		return temp;
	}
	else{
		return new Bullet(dir,position);
	}
}
