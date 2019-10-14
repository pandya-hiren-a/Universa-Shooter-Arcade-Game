#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Vector2.h"

//#include "Game.h"
class Game;

class Scene
{
public:
	struct gridLocation {
		int gridX;
		int gridY;
		bool isLocked;
		gridLocation(int x, int y, bool isL) {
			gridX = x;
			gridY = y;
			isLocked = isL;
		}
	};
	bool readyToSpawn = true;								// flag for dynamic enemy generation
	int tickCounter = 0;									// For capping
	Scene(Game*);
	~Scene();

	Game* game;
	virtual void Setup();
	void Cleanup();
	static std::vector<gridLocation> grid;											// Grid for enemies to arrive after movement
	void printGrid();
private:

	//std::list<GameObject*> gameObjects;
};

