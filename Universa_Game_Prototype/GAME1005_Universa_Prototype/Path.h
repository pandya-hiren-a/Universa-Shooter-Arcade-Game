#pragma once
#include <list>
#include "Vector2.h"

class Path
{
private:

public:
	Path() {}
	~Path() {}

	std::list<Vector2> Pathway;

	void AddNode(Vector2 v2)
	{
		Pathway.push_back(v2);
	}
};
