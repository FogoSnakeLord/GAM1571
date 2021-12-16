#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, int target,Tilemap* pTilemap)
    : GameObject(pMesh, pShader, pTexture, pos)
    , m_TargetTile(target)
    , m_PauseTimer(1.0f)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetWidth();
    m_Pathfinder = new Pathfinder(m_pTilemap);
    int index = pTilemap->WorldPositionToTileIndex(pos);
    validPath = m_Pathfinder->FindPath((index % m_MapWidth),(index / m_MapWidth),(target % m_MapWidth),(target/m_MapWidth));
    if (validPath) {
        m_Path = m_Pathfinder->GetPath((m_TargetTile % m_MapWidth), (m_TargetTile / m_MapWidth));
    }
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    int index;
    vec2 newPos;
    m_PauseTimer -= deltaTime;
    if (m_PauseTimer <= 0) {
        if (validPath) {
            index = m_Path.size();
            //Convert index to world Pos
            newPos = vec2((index % m_MapWidth), (index / m_MapWidth));
            //set current pos to new pos
            m_Position = newPos;
        }
        m_PauseTimer = 1.0f;
    }
}

