#pragma once
#include "GameObjectPool.h"
#include "Pickup.h"
class PickupPool: public GameObjectPool
{
public:
	PickupPool();
	~PickupPool();
	Pickup* GetPickup();
protected:

};

