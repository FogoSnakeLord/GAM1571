#include "Framework.h"
#include "Transform.h"
Transform::Transform(vec2 s, vec2 p) :
	m_Scale(s),
	m_Position(p)
{}
Transform::~Transform()
{
}
