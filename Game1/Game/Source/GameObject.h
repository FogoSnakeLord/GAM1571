#pragma once
#include "Framework.h"

typedef fw::vec2 vec2;
class GameObject {
public:
	

protected:
	fw::Mesh m_Mesh;
	std::vector<float> vertices;
	vec2 m_Position;
};