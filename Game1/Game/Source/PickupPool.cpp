#include "PickupPool.h"
#include "Random.h"

PickupPool::PickupPool()
{
}

PickupPool::~PickupPool()
{
}

Pickup* PickupPool::GetPickup()
{
	if (!m_Pool.empty()) {
		Pickup* temp = dynamic_cast <Pickup*> (m_Pool.back());
		m_Pool.pop_back();
		return temp;
	}
	else{
		return new Pickup();
	}
}
