#include "stdafx.h"
#include "Vector2.h"


//CONSTRUCTORS
Vector2::Vector2() : x(0), y(0) { }
Vector2::Vector2(float xValue, float yValue) : x(xValue), y(yValue) { }
Vector2::Vector2(const Vector2 & v) : x(v.x), y(v.y) { }
Vector2::Vector2(const Vector2 * v) : x(v->x), y(v->y) { }

//DECONSTRUCTOR
Vector2::~Vector2() { }

//METHODS
void Vector2::Set(float xValue, float yValue) { x = xValue; y = yValue; }

float Vector2::Length() const { return sqrt(x * x + y * y); }
float Vector2::LengthSquared() const { return x * x + y * y; }
float Vector2::Distance(const Vector2 & v) const { return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y))); }
float Vector2::DistanceSquared(const Vector2 & v) const { return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)); }
float Vector2::Dot(const Vector2 & v) const { return x * v.x + y * v.y; }

Vector2 Vector2::OrthoNormal() const { Vector2 ret; ret.x = -y, ret.y = x; return ret; }
Vector2 & Vector2::Normalized()
{
	Vector2 ret;
	ret.x = x;
	ret.y = y;
	return ret.Normalize();
}
Vector2 & Vector2::Normalize()
{
	if (Length() != 0)
	{
		float length = Length();
		x /= length; y /= length;
		return *this;
	}

	x = y = 0;
	return *this;
}