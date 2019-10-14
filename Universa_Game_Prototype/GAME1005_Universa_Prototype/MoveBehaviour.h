#pragma once
#include "SteeringBehaviour.h"
#include "MoveTarget.h"
class Enemies;
class MoveBehaviour :
	public SteeringBehaviour
{
public:
	MoveBehaviour(Enemies* e);
	//MoveBehaviour(GameObject* go);
	~MoveBehaviour();
	Target* target;
	void Update();
	void Setup();
	bool GetReady() { return (*target).ready; }
	void GetReady(bool x) { (*target).allReady = x; }
	
	//Vector2 target;
	//float maxSpeed = 15;
private:
	float angle = 0;
	//GameObject* go;
};
