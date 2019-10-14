#include "stdafx.h"
#include "Levels.h"
#include "Enemies.h"

//=============================================================LEVEL ONE(1)===============================================================//

Level1::Level1(Game* gPtr) : Scene(gPtr)
{
}


Level1::~Level1()
{
	Cleanup();
}

void Level1::Setup()
{
	Scene::Setup();
	// Grid creation moved to Game::init()
	Enemies::offsetX = 0;
	Enemies::offsetY = 0;
	int w = 0;
	game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(Scene::grid[0].gridX, Scene::grid[0].gridY), &grid[0], Vector2(0, 0)));
	Scene::grid[w].isLocked = true;

	for (int i = 1; i < 28; i++)																				// Creates 28 new enemies once Game is started
	{
		//cout << "Level 1 - W: " << w << endl;
		while (w < Scene::grid.size() && Scene::grid[w].isLocked) {
			++w;
		}
		if (w < Scene::grid.size()) {
			game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(Scene::grid[w].gridX, Scene::grid[w].gridY), &grid[w], Vector2(0, -50 * (1 + i))));												// Makes every other enemy a red enemy
			Scene::grid[w].isLocked = true;
		}
	}
}

void Level1::Update()
{
	// Creates 7 enemies every 8 seconds	(480 / 60 = 8 seconds)
	if(tickCounter % 600 == 0 && game->GetFSM()->getEnemies()->size() < 50 && readyToSpawn) {
		int w = 0;
		for (int i = 0; i < 7; i++)																				
		{
			while (w < grid.size() && grid[w].isLocked) {
				++w;
			}
			if (w < grid.size()) {
				game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * i)));
				grid[w].isLocked = true;
			}
		}
		readyToSpawn = false;
	}

	else {
		tickCounter++;
		readyToSpawn = true;
	}
}

//=============================================================LEVEL TWO(2)===============================================================//

Level2::Level2(Game* gPtr) : Scene(gPtr)
{
}


Level2::~Level2()
{
	Cleanup();
}

void Level2::Setup()
{
	Scene::Setup();

	Enemies::offsetX = 0;
	Enemies::offsetY = 0;
	int w = 0;
	game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(grid[0].gridX, grid[0].gridY), &grid[0], Vector2(0, 0)));
	grid[w].isLocked = true;

	for (int i = 1; i < 42; i++)																				// Creates 42 enemies in a level
	{
		while (w < grid.size() && grid[w].isLocked) {
			++w;
		}
		game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * (1 + i))));												// Makes every other enemy a red enemy
		grid[w].isLocked = true;
	}
}

void Level2::Update()
{
	// Creates 7 enemies every 5 seconds
	if (tickCounter % 300 == 0 && game->GetFSM()->getEnemies()->size() < 50 && readyToSpawn) {
		int w = 0;
		for (int i = 0; i < 7; i++)
		{
			while (w < grid.size() && grid[w].isLocked) {
				++w;
			}
			if (w < grid.size()) {
				game->GetFSM()->getEnemies()->push_back(new Enemies(1, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * i)));
				grid[w].isLocked = true;
			}
		}
		readyToSpawn = false;
	}
	else {
		tickCounter++;
		readyToSpawn = true;
	}
}

//=============================================================LEVEL THREE(3)===============================================================//

Level3::Level3(Game* gPtr) : Scene(gPtr)
{
}


Level3::~Level3()
{
	Cleanup();
}

void Level3::Setup()
{
	Scene::Setup();
	
	Enemies::offsetX = 0;
	Enemies::offsetY = 0;
	int w = 0;
	game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[0].gridX, grid[0].gridY), &grid[0], Vector2(0, 0)));
	grid[w].isLocked = true;

	for (int i = 1; i < 28; i++)																				// Creates 42 enemies in a level
	{
		while (w < grid.size() && grid[w].isLocked) {
			++w;
		}
		game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * (1 + i))));												// Makes every other enemy a red enemy
		grid[w].isLocked = true;
	}
}

void Level3::Update()
{
	// Creates 7 enemies every 15 seconds
	if (tickCounter % 300 == 0 && game->GetFSM()->getEnemies()->size() < 50 && readyToSpawn) {
		int w = 0;
		for (int i = 0; i < 7; i++)
		{
			while ( w < grid.size() && grid[w].isLocked) {
				++w;
			}
			if (w < grid.size()) {
				game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * i)));
				grid[w].isLocked = true;
			}
		}
		readyToSpawn = false;
	}
	else {
		tickCounter++;
		readyToSpawn = true;
	}
}

//=============================================================LEVEL FOUR(4)===============================================================//

Level4::Level4(Game* gPtr) : Scene(gPtr)
{
}


Level4::~Level4()
{
	Cleanup();
}

void Level4::Setup()
{
	Scene::Setup();
	
	Enemies::offsetX = 0;
	Enemies::offsetY = 0;
	int w = 0;
	game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[0].gridX, grid[0].gridY), &grid[0], Vector2(0, 0)));
	grid[w].isLocked = true;

	for (int i = 1; i < 42; i++)																				// Creates 42 enemies in a level
	{
		while (w < grid.size() && grid[w].isLocked) {
			++w;
		}
		game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * (1 + i))));												// Makes every other enemy a red enemy
		grid[w].isLocked = true;
	}
}

void Level4::Update()
{
	// Creates 7 enemies every 15 seconds
	if (tickCounter % 300 == 0 && game->GetFSM()->getEnemies()->size() < 50 && readyToSpawn) {
		int w = 0;
		for (int i = 0; i < 7; i++)
		{
			while ( w < grid.size() && grid[w].isLocked) {
				++w;
			}
			if (w < grid.size()) {
				game->GetFSM()->getEnemies()->push_back(new Enemies(2, 0, Vector2(grid[w].gridX, grid[w].gridY), &grid[w], Vector2(0, -50 * i)));
				grid[w].isLocked = true;
			}
		}
		readyToSpawn = false;
	}
	else {
		tickCounter++;
		readyToSpawn = true;
	}
}

//=============================================================LEVEL FIVE(5)===============================================================//

Level5::Level5(Game* gPtr) : Scene(gPtr)
{
}


Level5::~Level5()
{
	Cleanup();
}

void Level5::Setup()
{
	Scene::Setup();

	Enemies::offsetX = 1024/2 - 50;
	Enemies::offsetY = 50;
	
	for (int i = 0; i < 1; i++)																				
	{
		Boss* b = new Boss(game,3);
		game->GetFSM()->getEnemies()->push_back(b);															// Makes boss enemy
	}
}


/*EXTRAS

//#include "Bullet.h"
//#include "Game.h"
//#include "StateMachine.h"
//class Game;

vvvvv FOR LEVEL SETUP vvvvv
Scene::Setup();

	Enemies::offsetX = 0;
	Enemies::offsetY = 0;

	for (int i = 0; i < 21; i++)																				// Creates 21 new enemies once Game is started
	{
		game->GetFSM()->getEnemies()->push_back(new Enemies(1));												// Makes every other enemy a red enemy
		game->GetFSM()->getEnemies()->push_back(new Enemies(2));												// Makes every other enemy a green one
	}

vvvvv WAS UNDER BOSS STUFF vvvvv
//Enemies* e = new Enemies(4);
//game->GetFSM()->getEnemies()->push_back(e);

*/