#include "Pickup.h"
Pickup::Pickup(std::vector<float> v, int nV) :
    GameObject(v, nV)
    , m_IsActive(true)
{
    m_Position.x = 0.7f;
    m_Position.y = 0.5f;
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
