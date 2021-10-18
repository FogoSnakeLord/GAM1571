#include "GameObject.h"

GameObject::GameObject(std::vector<float> v, int nV):
	m_Mesh(nV,v)
	,m_Position(0.0f,0.0f)
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

	this->GetMesh()->Draw(m_pBasicShader);
}

