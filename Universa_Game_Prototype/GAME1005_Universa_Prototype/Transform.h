#pragma once
#include <SDL.h>
#include "Vector2.h"

class Transform
{
public:
	Transform();
	Transform(float x = 0, float y = 0, float _angle = 0, float xScale = 1, float yScale = 1);
	~Transform();

	Vector2 position;
	float angle;
	Vector2 scale;
};

