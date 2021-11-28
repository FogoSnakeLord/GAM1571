#pragma once
#include "DataTypes.h"
#include "Framework.h"
#include "SpriteSheet.h"
struct TileProperties {
    fw::Mesh* m_pSprite;
    fw::Texture* m_pTexture;
    bool m_Walkable;
    TileProperties(fw::Mesh* sprite, fw::Texture* texture, bool walk) :m_pSprite(sprite), m_pTexture(texture), m_Walkable(walk){}
    TileProperties(){}
};
class Tilemap
{
public:
    Tilemap(fw::ShaderProgram* shader, SpriteSheet* spriteSheet);
    ~Tilemap();
    void Draw(vec2 projScale, vec2 camPos);
protected:
    unsigned char* pTiles;
    TileProperties* m_TileProp;
    fw::ShaderProgram* m_pShader;
    SpriteSheet* m_pSpriteSheet;
};

