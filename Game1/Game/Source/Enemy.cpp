#include "Enemy.h"
Enemy::Enemy(std::vector<float> v, int nV) :
    GameObject(v, nV)
    , m_IsActive(true)
{
    m_Position.x = 0.5f;
    m_Position.y = 0.7f;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
}

void Enemy::Deactivate()
{
    m_IsActive = false;
}

bool Enemy::GetIsActive()
{
    return m_IsActive;
}
