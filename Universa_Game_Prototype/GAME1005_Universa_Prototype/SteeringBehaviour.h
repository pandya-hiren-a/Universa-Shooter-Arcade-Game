#pragma once
#include "Vector2.h"
//#include "Enemies.h"

class Enemies;
class SteeringBehaviour
{
public:
	SteeringBehaviour(Enemies*);
	~SteeringBehaviour();
	  
	virtual void Start();
	virtual void Update();
	virtual bool GetReady() { return 1; }
	virtual void GetReady(bool x) {}
	Vector2 velocity;
	float maxSpeed;
	float slowRadius = 0;
	float angularSpeed = 0.5f;

	Enemies* agent;
};