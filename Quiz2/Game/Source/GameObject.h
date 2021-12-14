#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Component.h"

class Game;


class GameObject
{
public:
    GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

protected:
    std::vector<Component*> m_Components;
};
