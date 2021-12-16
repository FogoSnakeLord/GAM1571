#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, int target,Tilemap* pTilemap)
    : GameObject(pMesh, pShader, pTexture, pos)
    , m_TargetTile(target)
    , m_PauseTimer(1.0f)
    , m_TargetLocation(pos)
    , state(0)
    , m_ResetCounter(0)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetWidth();
    m_Pathfinder = new Pathfinder(m_pTilemap);
    int index = pTilemap->WorldPositionToTileIndex(pos);
    validPath = m_Pathfinder->FindPath((index % m_MapWidth),(index / m_MapWidth),(target % m_MapWidth),(target/m_MapWidth));
    if (validPath) {
        m_Path = m_Pathfinder->GetPath((m_TargetTile % m_MapWidth), (m_TargetTile / m_MapWidth));
    }
    speed = 1.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    //searching state 1
    if (state == 0) {
        stateOneUpdate(deltaTime);
    }
    //patrolling state 2
    else if (state == 1) {
       stateTwoUpdate(deltaTime);
    }
    //Waiting state 3
}
void Enemy::stateOneUpdate(float deltaTime)
{
    int index;
    vec2 newPos;
    vec2 newTarget;
    if ((m_Position.x >= m_TargetLocation.x - 0.1) && (m_Position.x <= m_TargetLocation.x + 0.1) && (m_Position.y >= m_TargetLocation.y - 0.1) && (m_Position.y <= m_TargetLocation.y + 0.1)) {
        if (validPath && m_Path.size() > 0) {
            index = m_Path[m_Path.size() - 1];
            //Convert index to world Pos
            newTarget = vec2((index % m_MapWidth), (index / m_MapWidth));
            //set current pos to new pos
            m_TargetLocation = newTarget;
            m_Direction = vec2(abs(m_TargetLocation.x - m_Position.x), abs(m_TargetLocation.y - m_Position.y));
            m_Path.erase(m_Path.begin() + m_Path.size() - 1);
        }
        else if (m_Path.size() == 0) {
            state = 1;
        }
    }
    else {
        m_Direction = vec2(m_TargetLocation.x - m_Position.x, m_TargetLocation.y - m_Position.y);
        m_Direction.Normalize();
        m_Position += (m_Direction * deltaTime * speed);
    }
}
void Enemy::stateTwoUpdate(float deltaTime)
{
    if (m_PauseTimer > 0.75f) {
        m_Position += (vec2(1.0f, 0.0f) * deltaTime * speed);
    }
    else if (m_PauseTimer > 0.5f) {
        m_Position += (vec2(0.0f, 1.0f) * deltaTime * speed);
    }
    else if (m_PauseTimer > 0.25f) {
        m_Position += (vec2(-1.0f, 0.0f) * deltaTime * speed);
    }
    else {
        m_Position += (vec2(0.0f, -1.0f) * deltaTime * speed);
    }
    m_PauseTimer -= deltaTime;
    if (m_PauseTimer <= 0.0f) {
        m_PauseTimer = 1.0f;
        m_ResetCounter++;
        if (m_ResetCounter == 12) {
            state = 2;
        }
    }
}
/*int index;
    vec2 newPos;
    m_PauseTimer -= deltaTime;
    if (m_PauseTimer <= 0) {
        if (validPath&&m_Path.size()>0) {
            index = m_Path[m_Path.size()-1];
            //Convert index to world Pos
            newPos = vec2((index % m_MapWidth), (index / m_MapWidth));
            //set current pos to new pos
            m_Position = newPos;
            m_Path.erase(m_Path.begin()+ m_Path.size() - 1);
        }
        m_PauseTimer = 1.0f;
    }*/