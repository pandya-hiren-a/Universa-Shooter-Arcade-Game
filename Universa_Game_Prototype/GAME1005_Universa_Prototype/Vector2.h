#pragma once
#include <math.h>
class Vector2
{
public:
	//MEMBERS
	float x;
	float y;

	//CONSTRUCTORS
	Vector2();
	Vector2(float xValue, float yValue);
	Vector2(const Vector2 & v);
	Vector2(const Vector2 * v);

	//DECONSTRUCTOR
	~Vector2();

	//METHODS
	void Set(float xValue, float yValue);

	float Length() const;
	float LengthSquared() const;
	float Distance(const Vector2 & v) const;
	float DistanceSquared(const Vector2 & v) const;
	float Dot(const Vector2 & v) const;

	Vector2 OrthoNormal() const;
	Vector2 & Normalized();
	Vector2 & Normalize();

	//ASSINGMENT AND EQUALITY OPERATIONS
	inline Vector2 & operator= (const Vector2 & v) { x = v.x; y = v.y; return *this; }
	inline Vector2 & operator = (const float & f) { x = f; y = f; return *this; }
	inline Vector2 & operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const Vector2 & v) const { return (x == v.x) && (y == v.y); }
	inline bool operator != (const Vector2 & v) const { return (x != v.x) || (y != v.y); }

	//VECTOR2 TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (const Vector2 & v) const { return Vector2(x + v.x, y + v.y); }
	inline const Vector2 operator - (const Vector2 & v) const { return Vector2(x - v.x, y - v.y); }
	inline const Vector2 operator * (const Vector2 & v) const { return Vector2(x * v.x, y * v.y); }
	inline const Vector2 operator / (const Vector2 & v) const { return Vector2(x / v.x, y / v.y); }

	//VECTOR2 TO THIS OPERATIONS
	inline Vector2 & operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
	inline Vector2 & operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
	inline Vector2 & operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
	inline Vector2 & operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

	//SCALER TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
	inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
	inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
	inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

	//SCALER TO THIS OPERATIONS
	inline Vector2 & operator += (float v) { x += v; y += v; return *this; }
	inline Vector2 & operator -= (float v) { x -= v; y -= v; return *this; }
	inline Vector2 & operator *= (float v) { x *= v; y *= v; return *this; }
	inline Vector2 & operator /= (float v) { x /= v; y /= v; return *this; }
};

