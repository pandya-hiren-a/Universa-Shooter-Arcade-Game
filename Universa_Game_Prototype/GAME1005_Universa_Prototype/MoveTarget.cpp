#include "stdafx.h"
#include "MoveTarget.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
//#include "Game.h"

int Target::flip = 1;

Target::Target(Enemies* e, float x, float y)
{
	//target.x = x, target.y = y;
	
	if (e->gridIndex) {
		target.x = e->gridIndex->gridX + 100 * flip;//e->transform->position.x + 100.0f * (flip);
		target.y = e->gridIndex->gridY;//e->transform->position.x + 100.0f * (flip);
	}
	else {
		target.x = e->transform->position.x + 100.0f * (flip);
		target.y = e->transform->position.y;
	}
	//target.y = e->transform->position.y;
}

Target::~Target()
{
}

void Target::Update(Enemies* e)
{
	
	Vector2 targetDist = target - e->transform->position;
	if (targetDist.Length() <= 15) ready = true;

	if(allReady)
	{
		if (e->enemyType < 3) {
			e->alienBehaviour->maxSpeed = 80;
			//flip *= -1;
			//target.x += ((150.0f - targetDist.Length()) * flip);// Simply reverses the initial velocity, might not be good due to float rounding
			if (e->gridIndex) {
				target.x = e->gridIndex->gridX + 100.0f * flip;
			}
			else
				target.x = (e->transform->position.x + (100.0f - targetDist.Length()) * flip);// Simply reverses the initial velocity, might not be good due to float rounding

		}
		else {
			//flip *= -1;
			target.x = (e->transform->position.x + (150.0f - targetDist.Length()) * flip);// Simply reverses the initial velocity, might not be good due to float rounding
		}
		
		allReady = false;
		ready = false;
		/*bool control = true; // Random Move Targeting
		while (control)
		{
			moveBehaviour->target.x = 10 + (rand() % (gameObject->GetGame()->getScreenWidth() - 20));
			moveBehaviour->target.y = 10 + (rand() % ((gameObject->GetGame()->getScreenHeight() / 2) - 10));
			if (abs(moveBehaviour->target.x - gameObject->transform->position.x) >= 80 || abs(moveBehaviour->target.y - gameObject->transform->position.y) >= 80)
				control = false;
		}*/
	}
}
