#pragma once

#include "Framework.h"
#include "DataTypes.h"

class Game;

enum TileType
{
    TT_Empty,
    TT_Grass,
    TT_Stone,
    TT_Dirt,
    TT_NumTypes,
};

class Tilemap
{
    struct TileProperties
    {
        bool hasSprite;
        vec2 uvScale;
        vec2 uvOffset;
        bool walkable;
    };

public:
    Tilemap(Game* pGame, const TileType* pLayout, ivec2 layoutSize, vec2 tileSize);
    virtual ~Tilemap();

    void Draw(vec2 projScale, vec2 camPos);

    bool IsWorldPositionWalkable(vec2 worldPos);
    bool IsTileWalkable(int tileIndex);
    int GetWidth();
    int GetHeight();
    int WorldPositionToTileIndex(vec2 worldPos);
protected:
    void AddTileProperty(bool hasSprite, std::string name, bool walkable);

    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::SpriteSheet* m_pSpriteSheet;

    std::vector<TileProperties> m_TileProperties;

    TileType* m_pLayout;

    ivec2 m_LayoutSize;
    vec2 m_TileSize;
};
