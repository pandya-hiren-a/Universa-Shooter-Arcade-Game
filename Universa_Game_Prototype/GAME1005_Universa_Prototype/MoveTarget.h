#pragma once
#include "Vector2.h"
#include "SteeringBehaviour.h"
//#include "Move.h" // Will cause problems cause of loop
#include "Enemies.h"

class Target
{
public:
	Vector2 target;
	bool ready, allReady;
	//int flip = 1;
	static int flip;
	Target(Enemies* e, float=0, float=0);
	~Target();
	void Update(Enemies* e);

	//Move* moveBehaviour;
};