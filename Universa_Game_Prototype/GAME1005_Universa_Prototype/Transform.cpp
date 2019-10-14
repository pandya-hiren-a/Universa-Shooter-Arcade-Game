#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
	position.x = 0;
	position.y = 10;
}


Transform::Transform(float x, float y, float _angle, float xScale, float yScale)
{
	position.x = x;
	position.y = y;
	angle = _angle;
	scale.x = xScale;
	scale.y = yScale;
}


Transform::~Transform()
{
}
