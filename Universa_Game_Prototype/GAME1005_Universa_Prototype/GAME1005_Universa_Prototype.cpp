/**********************************
Filename: GAME1005_Universa_Prototype.cpp
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 27/03/2019
***********************************/

#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Spaceship.h"
#include "Bullet.h"
#include <SDL_ttf.h>
#include <vector>

using namespace std;
const int E_NO = 14 * 3; 															// Pre-defined number of enemies (Shall be changed in future to include dynamic assignments)
//void createEnemies(vector<Enemies*>&, int);

int main(int argc, char* args[])
{
	Game game;																		// Defining game object.
	Spaceship ship;																	// Spaceship (Player) object
	vector<Enemies*> enemy;															// Enemies objects vector
	int rNo = rand() % 5 + 1;														// Enemy type randomizer
	//createEnemies(enemy, rNo);
	game.init("Universa Prototype - Beta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0); // Init SDL and other modules

	while (game.running())															// Continue while the game is in running state
	{
		game.handleEvents();														// Check for the events to trigger the actions
		if (game.tick(enemy))														// To make processing capped at certain limit.
		{
			game.update(ship, (vector<Enemies*>&)enemy);							// Check for updates 
			//game.save();	
			game.render(ship, (vector<Enemies*>&)enemy);							// Render the updates	
			// Check if out of lives
			
			if (Bullet::m_iLives <= 0) {
				//enemy[0]->ResetStats();
				for (int i = 0; i < enemy.size(); i++) {
					delete enemy[i];
					enemy[i] = nullptr;
				}
				enemy.clear();
				rNo = rand() % 5 + 1;

				//createEnemies(enemy, rNo);

				for (int i = 0; i < game.bullets.size(); i++) {
					delete game.bullets[i];
					game.bullets[i] = nullptr;
				}
				game.bullets.clear();
				Bullet::m_iLives = 3;
				Bullet::m_iScore = 0;
				Bullet::m_iCurrentScore = 0;
				//game.bullets[0]->m_iLives = 3;
				//game.bullets[0]->m_iScore = 0;
				ship.m_rDst.x = 1024 / 2;
				ship.m_rDst.y = 670;
			}
			
		}
	}
	TTF_Quit();

	game.clean();																	// Clear the game objects and destroy modules
	return 0;
}

/*void createEnemies(vector<Enemies*>& e, int rand) {
	for (int i = 0; i < E_NO; i++) {
		if (i % rand == 0) {
			e.push_back(new Enemies(1));	// Type 1 Enemy
		}
		else {
			e.push_back(new Enemies(2));	// Type 2 Enemy
		}
	}
}*/