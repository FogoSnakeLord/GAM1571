#pragma once
#include "Framework.h"

typedef fw::vec2 vec2;
class GameObject {
public:
	GameObject(std::vector<float> v, int nV);
	virtual ~GameObject();
	fw::Mesh* GetMesh();
	vec2 GetPosition();
	void Draw(fw::ShaderProgram* m_pBasicShader, float timePassed);
	void SetColour(float r,float g, float b);
	void SetVary(float newVaries);
	float GetVary();
	void SetPosition(vec2 newPosition);
protected:
	fw::Mesh m_Mesh;
	vec2 m_Position;
	float m_R;
	float m_G;
	float m_B;
	float m_Varies;
};