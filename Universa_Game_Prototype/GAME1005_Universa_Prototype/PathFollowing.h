#pragma once
#include "Arrive.h"
#include <list>
#include "Vector2.h"
class PathFollowing :
	public Arrive
{
public:
	PathFollowing(Enemies*, int, Vector2, Vector2);
	~PathFollowing();

	virtual void Start();
	virtual void Update();
	static void prepareWaypoints();

	std::list<Vector2> waypoints;
	float distanceThreshold = 5;
	static std::list<Vector2>* leftSide;
	static std::list<Vector2>* rightSide;

	std::list<Vector2>::iterator currentWaypoint;
};

