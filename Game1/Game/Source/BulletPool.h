#pragma once
#include "GameObjectPool.h"
#include "Bullet.h"
class BulletPool: public GameObjectPool
{
public:
	BulletPool();
	~BulletPool();
	Bullet* GetBullet(vec2 dir, vec2 position);
protected:

};

