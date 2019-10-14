#include "stdafx.h"
#include <cmath>
//#include "Game.h"
#include "MoveBehaviour.h"
#include "Transform.h"
#include "Vector2.h"
#include "Enemies.h"
//#include "MoveBehaviourTarget.h"


MoveBehaviour::MoveBehaviour(Enemies* e) :SteeringBehaviour(e)
{
	target = new Target(e); // defaults to 0,0
	//target.x = 0, target.y = 0; // Default target
}

//MoveBehaviour::MoveBehaviour(GameObject * go) : SteeringBehaviour(go){}

MoveBehaviour::~MoveBehaviour()
{
}

void MoveBehaviour::Update()
{
	
		{// Updates target
			target->Update(agent);
		}
		{// Updates velocity of enemy towards the target
			velocity.x = target->target.x - agent->transform->position.x;
			velocity.y = target->target.y - agent->transform->position.y;
			float distance = velocity.Length();
			velocity = (velocity / distance) * (slowRadius > distance ? distance : maxSpeed);
		}
		{// Moves the position of the enemy a sixtieth of velocity to comply with a framerate of 60 FPS
			agent->transform->position += velocity / 60.0f;
		}
}

void MoveBehaviour::Setup()
{
}

