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
    void stateOneUpdate(float deltaTime);
    void stateTwoUpdate(float deltaTime);
    //virtual void Draw() override;
protected:
    int m_TargetTile;
    std::vector<int> m_Path;
    Pathfinder* m_Pathfinder;
    bool validPath;
    int m_MapWidth;
    vec2 m_TargetLocation;
    vec2 m_Direction;
    float speed;
    float m_PauseTimer;
    int state;
    int m_ResetCounter;
};
