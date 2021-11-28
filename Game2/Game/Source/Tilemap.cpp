#include "Tilemap.h"
#include "Constants.h"

Tilemap::Tilemap(fw::ShaderProgram* shader, SpriteSheet* spriteSheet):
    m_pShader(shader)
    , m_pSpriteSheet(spriteSheet)
{
	pTiles = new unsigned char[MAP_WIDTH*MAP_HEIGHT];
    //reads the list backwards from index 35 an assigns the correct tile to the correct index 
    for (int r = 0; r < MAP_HEIGHT; r++) {
        for (int c = (MAP_WIDTH - 1); c >= 0; c--) {
            pTiles[(MAP_WIDTH*((MAP_HEIGHT-1)-r))+c] = TILES[(r * MAP_HEIGHT) + c];
        }
    }
    std::vector<fw::VertexFormat> spriteVerts =
    {
        { vec2(0.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) }, // top left
        { vec2(0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) }, // bottom left
        { vec2(1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) }, // top right
        { vec2(1.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) }, // bottom right
    };

    fw::Mesh* pMesh = new fw::Mesh(GL_TRIANGLE_STRIP, spriteVerts);
    fw::Texture* pTexture = new fw::Texture("Data/Textures/Sprites.png");
	m_TileProp = new TileProperties[TileType::NumTypes];
    for (int i = 0; i < TileType::NumTypes; i++) {
        m_TileProp[i].m_pSprite = pMesh;
        m_TileProp[i].m_pTexture = pTexture;
    }
    m_TileProp[0].m_Walkable = true;
    m_TileProp[1].m_Walkable = true;
    m_TileProp[2].m_Walkable = true;
    m_TileProp[3].m_Walkable = false;
    m_TileProp[4].m_Walkable = false;

}

Tilemap::~Tilemap()
{

}

void Tilemap::Draw(vec2 projScale, vec2 camPos)
{
    //vec2((i % MAP_WIDTH) * 64, (i / MAP_WIDTH) * 64)
    //vec2(0.0f,0.0f)
    vec2 m_Scale = vec2(4, 3);
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        if (pTiles[i]== TileType::Grass) {
            m_TileProp[0].m_pSprite->Draw(m_pShader, m_TileProp[0].m_pTexture, projScale, camPos, m_Scale, vec2((i % MAP_WIDTH)-4.0f, (i / MAP_WIDTH) - 3.0f), 0.0f, (m_pSpriteSheet->GetSpriteInfo("ground_05"))->UvScale, (m_pSpriteSheet->GetSpriteInfo("ground_05"))->UvOffset);
        }
        else if (pTiles[i] == TileType::Rock) {
            m_TileProp[1].m_pSprite->Draw(m_pShader, m_TileProp[1].m_pTexture, projScale, camPos, m_Scale, vec2((i % MAP_WIDTH) - 4.0f, (i / MAP_WIDTH) - 3.0f), 0.0f, (m_pSpriteSheet->GetSpriteInfo("ground_06"))->UvScale, (m_pSpriteSheet->GetSpriteInfo("ground_06"))->UvOffset);
        }
        else if (pTiles[i] == TileType::Cheese) {
            m_TileProp[2].m_pSprite->Draw(m_pShader, m_TileProp[2].m_pTexture, projScale, camPos, m_Scale, vec2((i % MAP_WIDTH) - 4.0f, (i / MAP_WIDTH) - 3.0f), 0.0f, (m_pSpriteSheet->GetSpriteInfo("ground_01"))->UvScale, (m_pSpriteSheet->GetSpriteInfo("ground_01"))->UvOffset);
        }
        else if (pTiles[i] == TileType::Water) {
            m_TileProp[3].m_pSprite->Draw(m_pShader, m_TileProp[3].m_pTexture, projScale, camPos, m_Scale, vec2((i % MAP_WIDTH) - 4.0f, (i / MAP_WIDTH) - 3.0f), 0.0f, (m_pSpriteSheet->GetSpriteInfo("crate_04"))->UvScale, (m_pSpriteSheet->GetSpriteInfo("crate_04"))->UvOffset);
        }
        else if (pTiles[i] == TileType::Wall) {
            m_TileProp[4].m_pSprite->Draw(m_pShader, m_TileProp[4].m_pTexture, projScale, camPos, m_Scale, vec2((i % MAP_WIDTH) - 4.0f, (i / MAP_WIDTH) - 3.0f), 0.0f, (m_pSpriteSheet->GetSpriteInfo("block_01"))->UvScale, (m_pSpriteSheet->GetSpriteInfo("block_01"))->UvOffset);
        }
    }
}
