#include "stdafx.h"
#include "Scene.h"
#include "Enemies.h"
#include "Game.h"

std::vector<Scene::gridLocation> Scene::grid;

Scene::Scene(Game* gPtr)
{
	game = gPtr;
}

Scene::~Scene()
{

}

void Scene::Setup()
{
	printGrid();
}

void Scene::Cleanup()
{
	for (Enemies* e : *game->GetFSM()->getEnemies())
	{
		delete e;
		e = nullptr;
	}
	game->GetFSM()->getEnemies()->clear();
	for (Bullet* b : game->bullets)
	{
		delete b;
		b = nullptr;
	}
	game->bullets.clear();
	for (Lazer* l : game->lazers)
	{
		delete l;
		l = nullptr;
	}
	game->lazers.clear();
	for (Explosion* exp : game->explode)
	{
		delete exp;
		exp = nullptr;
	}
	game->explode.clear();

	int w = 0;
	while (w < Scene::grid.size() && Scene::grid[w].isLocked) {
		Scene::grid[w++].isLocked = false;
	}
}

void Scene::printGrid()
{
	int w = 0;
	while (w < grid.size()) {
		cout << (grid[w++].isLocked) ? "Locked" : "Unlocked";
		cout << " ";
		if (w % 14 == 0)
			cout << endl;
	}
}

/*EXTRAS
//#include "Bullet.h"
//#include "Powerup.h"
//class Game;

VVVVV UNDER SCENE CLEANUP VVVVV
	/*for (unsigned int i = 0; i < game->GetFSM()->getEnemies()->size(); i++)
	{
		game->GetFSM()->getEnemies()->erase(game->GetFSM()->getEnemies()->begin() + i);
		if (game->GetFSM()->getEnemies()->at(i) != nullptr)
		{
			Enemies* temp = game->GetFSM()->getEnemies()->at(i);
			game->GetFSM()->getEnemies()->erase(game->GetFSM()->getEnemies()->begin() + i);
			delete temp;
		}
	}*/
	/*
	for (unsigned int i = 0; i < game->bullets.size(); i++)
	{
		if (game->bullets[i] != nullptr)
		{
			Bullet* temp = game->bullets[i];
			game->bullets.erase(game->bullets.begin() + i);
			delete temp;
		}
	}*/
	/*for (GameObject* go : gameObjects)
	{
		game->Destroy(go);
	}*/
	//gameObjects.clear();