#include "stdafx.h"
#include "PathFollowing.h"
#include "Game.h"
#include "MoveBehaviour.h"
list<Vector2>* PathFollowing::leftSide = new list<Vector2>;
list<Vector2>* PathFollowing::rightSide = new list<Vector2>;

PathFollowing::PathFollowing(Enemies* e, int i, Vector2 vec, Vector2 vecOffset) :Arrive(e)
{	

	// Copy path nodes to waypoint nodes
	list<Vector2>::iterator iter;
	
	if (i % 2 == 0) {
		waypoints.push_back((*leftSide).front() + vecOffset);
		for (iter = (*leftSide).begin(); iter != (*leftSide).end(); iter++)
		{
			Vector2 temp = *iter;
			waypoints.push_back(temp);
		}
		iter = (*leftSide).begin();
		iter++;
		target = new Transform((*iter).x, (*iter).y);
	}
	else {
		waypoints.push_back((*rightSide).front() + vecOffset);
		for (iter = (*rightSide).begin(); iter != (*rightSide).end(); iter++)
		{
			Vector2 temp = *iter;
			waypoints.push_back(temp);
		}
		iter = (*rightSide).begin();
		iter++;
		target = new Transform((*iter).x, (*iter).y);
		//target = new Transform((*rightSide).begin()->x, (*rightSide).begin()->y);
	}
	waypoints.push_back(vec);
	//Start();
}

PathFollowing::~PathFollowing()
{
}

void PathFollowing::Start()
{
	currentWaypoint = waypoints.begin();

	float distance = (agent->transform->position - *currentWaypoint).Length();
	float currentDistance = 0;
	for (std::list<Vector2>::iterator it = waypoints.begin(); it != waypoints.end(); ++it)		// Finds the closest node
	{
		currentDistance = (agent->transform->position - *it).Length();
		if (currentDistance < distance)
		{
			distance = currentDistance;
			currentWaypoint = it;
		}
	}

	target->position.operator=(*currentWaypoint);

	Arrive::Start();
}

void PathFollowing::Update()
{
	if ((target->position - agent->transform->position).Length() < distanceThreshold)
	{
		if (currentWaypoint != waypoints.end())
		{
			++currentWaypoint;
			if (currentWaypoint != waypoints.end())
			{
				target->position.operator=(*currentWaypoint);
			}
		}
	}

	if(currentWaypoint != waypoints.end())
		Arrive::Update();
	else {
		agent->transform->angle = atan2(0, 0) * 180.0f / M_PI;
		agent->SwitchMove(Enemies::MoveType::Standard);
	}
}

void PathFollowing::prepareWaypoints()
{
	PathFollowing::leftSide->clear();
	PathFollowing::leftSide->push_back(new Vector2(-100, -100));
	PathFollowing::leftSide->push_back(new Vector2(0, 0));
	PathFollowing::leftSide->push_back(new Vector2(256, 460));
	PathFollowing::leftSide->push_back(new Vector2(512, 512));
	PathFollowing::leftSide->push_back(new Vector2(600, 495));
	PathFollowing::leftSide->push_back(new Vector2(684, 384));
	/*PathFollowing::leftSide->push_back(new Vector2(60, 100));
	PathFollowing::leftSide->push_back(new Vector2(120, 220));
	PathFollowing::leftSide->push_back(new Vector2(180, 400));
	PathFollowing::leftSide->push_back(new Vector2(240, 500));
	PathFollowing::leftSide->push_back(new Vector2(280, 512));
	PathFollowing::leftSide->push_back(new Vector2(350, 520));
	PathFollowing::leftSide->push_back(new Vector2(400, 521));
	PathFollowing::leftSide->push_back(new Vector2(450, 512));
	PathFollowing::leftSide->push_back(new Vector2(500, 500));
	PathFollowing::leftSide->push_back(new Vector2(550, 400));*/

	PathFollowing::rightSide->clear();
	PathFollowing::rightSide->push_back(new Vector2(1100, -100));
	PathFollowing::rightSide->push_back(new Vector2(1024, 0));
	PathFollowing::rightSide->push_back(new Vector2(768, 460));
	PathFollowing::rightSide->push_back(new Vector2(512, 512));
	PathFollowing::rightSide->push_back(new Vector2(424, 495));
	PathFollowing::rightSide->push_back(new Vector2(340, 384));
	

}
