#pragma once
#include "Framework.h"
#include "SpriteSheet.h"
struct TileProperties {
    fw::Mesh* m_pSprite;
    fw::Texture* m_pTexture;
    bool m_Walkable;
};
class Tilemap
{
public:
    Tilemap();
    ~Tilemap();
protected:
    unsigned char* pTiles[];
};

