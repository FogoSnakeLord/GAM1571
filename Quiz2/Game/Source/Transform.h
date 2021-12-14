#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Component.h"
class Transform: public Component
{
public:
	Transform(vec2 s, vec2 p);
	~Transform();
	vec2 m_Scale;
	vec2 m_Position;
};
