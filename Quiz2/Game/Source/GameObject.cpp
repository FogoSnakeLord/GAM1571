#include "Framework.h"

#include "GameObject.h"
#include "Transform.h"
#include "Renderable.h"
GameObject::GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos)
{
    Transform* t = new Transform(scale, pos);
    m_Components.push_back(t);
    Renderable* r = new Renderable(pMesh, pShader);
    m_Components.push_back(r);
}

GameObject::~GameObject()
{
    for (int i = 0; i < m_Components.size(); i++) {
        delete m_Components[i];
    }
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 projScale, vec2 camPos)
{   
    vec2 tempScale;
    vec2 tempPos;
    Transform* tempTransform;
    Renderable* tempRenderable;
    for (int i = 0; i < m_Components.size(); i++) {
        tempTransform = dynamic_cast<Transform*>(m_Components[i]);
        if (tempTransform != nullptr) {
            tempScale = tempTransform->m_Scale;
            tempPos = tempTransform->m_Position;
        }
    }
    for (int i = 0; i < m_Components.size(); i++) {
        tempRenderable = dynamic_cast<Renderable*>(m_Components[i]);
        if (tempRenderable != nullptr) {
            (tempRenderable->m_Mesh)->Draw(tempRenderable->m_Shader, nullptr, projScale, camPos, tempScale, tempPos, vec2(1, 1), vec2(0, 0), 0.0f);
        }
    }
}
