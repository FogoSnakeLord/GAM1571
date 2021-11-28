#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "SpriteSheet.h"
class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, std::string spriteName, SpriteSheet* spriteSheet);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

    bool IsCollidingWith(GameObject* pOtherObject);

    void SetTexture(fw::Texture* pTexture) { m_pTexture = pTexture; }

protected:
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;
    std::string m_SpriteName;
    SpriteSheet* m_pSpriteSheet;
    vec2 m_Position;

    float m_Radius;
};
