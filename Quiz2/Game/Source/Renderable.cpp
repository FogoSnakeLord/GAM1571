#include "Framework.h"
#include "Renderable.h"


Renderable::Renderable(fw::Mesh* m, fw::ShaderProgram* s) :
	m_Mesh(m),
	m_Shader(s)
{}

Renderable::~Renderable()
{
}
