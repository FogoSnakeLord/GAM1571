#include "Enemy.h"
#include "Random.h"
Enemy::Enemy(std::vector<float> v, int nV) :
    GameObject(v, nV)
    , m_IsActive(true)
{
    Random* r=new Random();
    m_Position.x = r->RandFloat(-1.0f,1.0f);
    m_Position.y = r->RandFloat(-1.0f, 1.0f);
    delete r;
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
