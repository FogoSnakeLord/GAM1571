#include "Pickup.h"
#include "Random.h"
Pickup::Pickup() :
    GameObject(std::vector<float>{
    0.0f, 0.0f, 1.0f, 0.02f, -0.02f, 1.0f,
        0.02f, -0.02f, 1.0f, 0.02f, -0.04f, 1.0f,
        0.02f, -0.04f, 1.0f, 0.0f, -0.06f, 1.0f,
        0.0f, -0.06f, 1.0f, -0.02f, -0.04f, 1.0f,
        -0.02f, -0.04f, 1.0f, -0.02f, -0.02f, 1.0f,
        -0.02f, -0.02f, 1.0f, 0.0f, 0.0f, 1.0f }, 12)
    , m_IsActive(true)
{
    Init();
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

void Pickup::Init()
{
    Random* r = new Random();
    m_Position.x = r->RandFloat(-1.0f, 1.0f);
    m_Position.y = r->RandFloat(-1.0f, 1.0f);
    delete r;
    m_IsActive = false;
}
