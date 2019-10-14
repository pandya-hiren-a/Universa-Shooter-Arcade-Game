#include "stdafx.h"
#include "Arrive.h"
#include "Game.h"


Arrive::Arrive(Enemies* e) :SteeringBehaviour(e)
{
}

void Arrive::Update()
{
	// Get direction to target
	Vector2 direction = target->position - agent->transform->position;
	float distance = direction.Length();
	direction.Normalize();
	agent->transform->position += (direction * maxSpeed) / 60.0f;

	agent->transform->angle = atan2(direction.y, direction.x) * 180.0f / M_PI - 90.0f;
	// Check if we are there
	/*if (distance < targetRadius 
	{
		return;
	}
	float targetSpeed = 0;
	// If we are outside the slowRadius, go to maxSpeed
	if (distance > slowRadius)
	{
		targetSpeed = maxSpeed;
	}
    // Otherwise calculate scaled speed
	else
	{
		targetSpeed = maxSpeed * distance / slowRadius;
	}
	// The target velocity combines speed and direction
	Vector2 targetVelocity = direction;
	targetVelocity.Normalize();
	targetVelocity *= targetSpeed;*/

	SteeringBehaviour::Update();
}
