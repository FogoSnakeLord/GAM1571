#include "Player.h"
#include "Random.h"
Player::Player(std::vector<float> v, int nV, fw::FWCore& fwCore) :
    GameObject(v,nV)
    , m_FWCore(fwCore)
    , m_Score(0)
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

void Player::Respawn()
{
    Random* r = new Random();
    m_Position.x = r->RandFloat(-1.0f, 1.0f);
    m_Position.y = r->RandFloat(-1.0f, 1.0f);
    delete r;
}

void Player::ChangeScore(int score)
{
    m_Score += score;
}

int Player::GetScore()
{
    return m_Score;
}
