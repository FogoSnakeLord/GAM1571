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
    int index;
    index = m_pTilemap->WorldPositionToTileIndex(m_Position);
    if (((m_pTilemap->getTileType(index))==TileType::TT_Stone)) {
        m_pTilemap->ChangeTileTypeAtLocation(TileType::TT_Dirt, index);
    }
    //If Left is pressed
    if (m_pPlayerController->IsLeftShooting())
    {
        for (int i = 0; i < m_pTilemap->GetWidth(); i++) {
            if ((index % m_pTilemap->GetWidth()) != 0) {
                index--;
                if (m_pTilemap->getTileType(index) == TileType::TT_Dirt) {
                    m_pTilemap->ChangeTileTypeAtLocation(TileType::TT_Grass, index);
                }
            }
            else {
                break;
            }
        }
    }
    //Right
    index = m_pTilemap->WorldPositionToTileIndex(m_Position);
    if (m_pPlayerController->IsRightShooting())
    {
        for (int i = 0; i < m_pTilemap->GetWidth(); i++) {
            if ((index % m_pTilemap->GetWidth()) != m_pTilemap->GetWidth()-1) {
                index++;
                if (m_pTilemap->getTileType(index) == TileType::TT_Dirt) {
                    m_pTilemap->ChangeTileTypeAtLocation(TileType::TT_Grass, index);
                }
            }
            else {
                break;
            }
        }
    }
    //Up
    index = m_pTilemap->WorldPositionToTileIndex(m_Position);
    if (m_pPlayerController->IsUpShooting())
    {
        for (int i = 0; i < m_pTilemap->GetWidth(); i++) {
            if ((index+10)<(m_pTilemap->GetWidth()*m_pTilemap->GetHeight())) {
                index+=10;
                if (m_pTilemap->getTileType(index) == TileType::TT_Dirt) {
                    m_pTilemap->ChangeTileTypeAtLocation(TileType::TT_Grass, index);
                }
            }
            else {
                break;
            }
        }
    }
    //Down
    index = m_pTilemap->WorldPositionToTileIndex(m_Position);
    if (m_pPlayerController->IsDownShooting())
    {
        for (int i = 0; i < m_pTilemap->GetWidth(); i++) {
            if ((index - 10) > 0) {
                index -= 10;
                if (m_pTilemap->getTileType(index) == TileType::TT_Dirt) {
                    m_pTilemap->ChangeTileTypeAtLocation(TileType::TT_Grass, index);
                }
            }
            else {
                break;
            }
        }
    }
}
