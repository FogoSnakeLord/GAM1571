#include "Player.h"
Player::Player(std::vector<float> v, int nV, fw::FWCore& fwCore) :
    GameObject(v,nV)
    , m_FWCore(fwCore)
{
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    float speed = 1.0f;

    if (m_FWCore.IsKeyDown('D'))
    {
        m_Position.x += speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('S'))
    {
        m_Position.y -= speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('A'))
    {
        m_Position.x -= speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('W'))
    {
        m_Position.y += speed * deltaTime;
    }
}