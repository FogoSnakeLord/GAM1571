#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"
#include "Tilemap.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pTexture, pos )
    , m_pPlayerController( pController )
{
}

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pSpriteSheet, pos )
    , m_pPlayerController( pController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 5.0f;

    vec2 newPos = m_Position;

    // Try moving up/down.
    if( m_pPlayerController->IsUpHeld() )
    {
        newPos.y += speed * deltaTime;
    }
    if( m_pPlayerController->IsDownHeld() )
    {
        newPos.y -= speed * deltaTime;
    }

    if( m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.3f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.3f) ) )
    {
        m_Position = newPos;
    }

    // Try moving left/right.
    newPos = m_Position;
    if( m_pPlayerController->IsLeftHeld() )
    {
        newPos.x -= speed * deltaTime;
    }
    if( m_pPlayerController->IsRightHeld() )
    {
        newPos.x += speed * deltaTime;
    }

    if( m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.3f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.3f) ) )
    {
        m_Position = newPos;
    }

    if( m_pSpriteSheet )
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName( "player_06" );
        m_UVScale = info.uvScale;
        m_UVOffset = info.uvOffset;
    }
}
