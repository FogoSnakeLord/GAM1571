#include "Enemy.h"
#include "Random.h"
Enemy::Enemy(int type) :
    GameObject(std::vector<float>{
    0.0f, 0.0f, 1.0f, 0.05f, 0.05f, 1.0f,
        0.05f, 0.05f, 1.0f, 0.1f, 0.05f, 1.0f,
        0.1f, 0.05f, 1.0f, 0.15f, 0.0f, 1.0f,
        0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, }, 8)
    , m_IsActive(true)
    , m_MoveCounter(0)
{
    Init(type);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
    m_MoveCounter++;
    if (m_Type == 1) {
        if (m_MoveCounter<5000) {
            m_Position.x = m_Position.x + 0.35f*deltaTime;
        }
        else if (m_MoveCounter <= 10000) {
            m_Position.x = m_Position.x - 0.35f * deltaTime;
        }
        else {
            m_MoveCounter = 0;
        }
    }
    else {
        if (m_MoveCounter < 5000) {
            m_Position.y = m_Position.y + 0.35f * deltaTime;
        }
        else if (m_MoveCounter <= 10000) {
            m_Position.y = m_Position.y - 0.35f * deltaTime;
        }
        else {
            m_MoveCounter = 0;
        }
    }
}

void Enemy::Deactivate()
{
    m_IsActive = false;
}

bool Enemy::GetIsActive()
{
    return m_IsActive;
}

void Enemy::Init(int type)
{
    m_Type = type;
    if (type==1) {
        m_B = 0.8f;
        m_G = 0.0f;
    }
    else {
        m_G = 0.7f;
        m_B = 0.0f;
    }
    Random* r = new Random();
    m_Position.x = r->RandFloat(-1.0f, 1.0f);
    m_Position.y = r->RandFloat(-1.0f, 1.0f);
    delete r;
    m_IsActive = false;
}
