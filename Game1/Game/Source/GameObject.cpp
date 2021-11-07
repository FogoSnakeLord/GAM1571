#include "GameObject.h"

GameObject::GameObject(std::vector<float> v, int nV):
	m_Mesh(nV,v)
	,m_Position(0.0f,0.0f)
	, m_R(0.0f)
	, m_G(0.0f)
	, m_B(0.0f)
	, m_Varies(0.0f)
{
}

GameObject::~GameObject()
{
	delete& m_Mesh;
}

fw::Mesh* GameObject::GetMesh()
{
	return &m_Mesh;
}

vec2 GameObject::GetPosition()
{
	return m_Position;
}

void GameObject::Draw(fw::ShaderProgram* m_pBasicShader, float timePassed)
{
	glUseProgram(m_pBasicShader->GetProgram());

	GLint u_Offset = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Offset");
	glUniform2f(u_Offset, m_Position.x, m_Position.y);

	GLint u_Time = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Time");
	glUniform1f(u_Time, timePassed);

	GLint u_Red = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Red");
	glUniform1f(u_Red, m_Varies);

	GLint u_Colour = glGetUniformLocation(m_pBasicShader->GetProgram(), "u_Colour");
	glUniform4f(u_Colour, m_R,m_G,m_B,1.0f);

	this->GetMesh()->Draw(m_pBasicShader);
}

void GameObject::SetColour(float r, float g, float b)
{
	m_R = r;
	m_G = g;
	m_B = b;
}

void GameObject::SetVary(float newVaries)
{
	m_Varies = newVaries;
}

float GameObject::GetVary()
{
	return m_Varies;
}

void GameObject::SetPosition(vec2 newPosition)
{
	m_Position = newPosition;
}

