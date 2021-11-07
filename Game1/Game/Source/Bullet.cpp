#include "Bullet.h"
#include "Random.h"
Bullet::Bullet(vec2 dir, vec2 position) :
    GameObject(std::vector<float>{0.010f, 0.010f, 1.0f, -0.010f, 0.010f, 1.0f, -0.010f, 0.010f, 1.0f, -0.010f, -0.01f, 1.0f, -0.010f, -0.01f, 1.0f, 0.010f, -0.010f, 1.0f, 0.010f, -0.01f, 1.0f, 0.010f, 0.010f, 1.0f}, 8)
{
    //std::vector<float> {0.10f, 0.10f, 1.0f, -0.10f, 0.10f, 1.0f, -0.10f, 0.10f, 1.0f, -0.10f, -0.1f, 1.0f, -0.10f, -0.1f, 1.0f, 0.10f, -0.10f, 1.0f, 0.10f, -0.1f, 1.0f, 0.10f, 0.10f, 1.0f}, 8
    Init(dir,position);
}

Bullet::~Bullet()
{

}

void Bullet::Init( vec2 dir, vec2 position)
{
    m_Position = position;
    m_Dir = dir;
}

void Bullet::Update(float deltaTime)
{
    float speed = 0.2f;
    m_Position += m_Dir*speed*deltaTime;
}

