#pragma once
#include "SteeringBehaviour.h"
#include "Transform.h"
class Arrive :
	public SteeringBehaviour
{
public:
	Arrive(Enemies*);

	virtual void Update();

	Transform* target;
	float maxAccelaraction = 100;
	float slowRadius = 300;
	float targetRadius = 5;
	float timeToTarget = 1.0f;
};

