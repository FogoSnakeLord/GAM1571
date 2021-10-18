#include "Pickup.h"
#include "Random.h"
Pickup::Pickup(std::vector<float> v, int nV) :
    GameObject(v, nV)
    , m_IsActive(true)
{
    Random* r = new Random();
    m_Position.x = r->RandFloat(-1.0f, 1.0f);
    m_Position.y = r->RandFloat(-1.0f, 1.0f);
    delete r;
}

Pickup::~Pickup()
{

}

void Pickup::Deactivate()
{
    m_IsActive = false;
}

bool Pickup::GetIsActive()
{
    return m_IsActive;
}
