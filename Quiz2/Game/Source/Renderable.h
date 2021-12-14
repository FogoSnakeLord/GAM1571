#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Component.h"
class Renderable: public Component
{
public:
	Renderable(fw::Mesh* m, fw::ShaderProgram* s);
	~Renderable();
	fw::Mesh* m_Mesh;
	fw::ShaderProgram* m_Shader;
};
