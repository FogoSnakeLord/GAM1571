#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Pathfinder.h"

class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, int target, Tilemap* pTileMap);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;
protected:
    int m_TargetTile;
    std::vector<int> m_Path;
    Pathfinder* m_Pathfinder;
    bool validPath;
    int m_MapWidth;
    float m_PauseTimer;
};
