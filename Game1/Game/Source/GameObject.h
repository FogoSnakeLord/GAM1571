#pragma once
#include "Framework.h"

typedef fw::vec2 vec2;
class GameObject {
public:
	GameObject(std::vector<float> v, int nV);
	~GameObject();
	fw::Mesh* GetMesh();
	vec2 GetPosition();
	void Draw(fw::ShaderProgram* m_pBasicShader, float timePassed);

protected:
	fw::Mesh m_Mesh;
	vec2 m_Position;
};