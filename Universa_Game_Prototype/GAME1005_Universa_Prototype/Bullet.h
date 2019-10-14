/**********************************
Filename: Bullet.h
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 26/01/2019
***********************************/
#pragma once
#include <chrono>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Enemies.h"
#include "Spaceship.h"
#include <cmath>
#include "Powerup.h"
#include "Timer.h"
using namespace std;
using namespace chrono;

class Bullet {
public:
	SDL_Rect m_rSrc;																			// Source rectangle to facilitate rendering
	SDL_Rect m_rDst;																			// Destination rectangle to facilitate rendering 
	static int m_iSpeed;																		// Bullet movement speed. Only one instance of this is created ever. 
	static double m_dLifespan;																	// Bullet lifespan after it has been fired
	static int m_iScore;
	static int m_iPrevScore;
	static int m_iCurrentScore;
	static int m_iLives;

	bool playerHit = false;
	bool m_bKillMeNow = false;																	// If bullet should be removed from the render screen
	double m_Dx;																				// Delta for X coordinate movement
	double m_Dy;																				// Delta for Y coordinate movement
	double m_dElapsed = 0.0;																	// Time counter to count passed moments after the bullet has been fired
	bool playerOwned = false;																	// To check if the bullet has been fired by the player
	steady_clock::time_point m_lastTime;														// Last update time to confirm bullet lifespan
	steady_clock::time_point m_thisTime;														// Current time to confirm bullet lifespan
	
	// Bullet constructor
	Bullet()
	{
		m_rSrc.x = m_rSrc.y = 0;																// Default positioning
		m_rSrc.w = m_rSrc.h = m_rDst.w = m_rDst.h = 32;											// Default height/width
		m_lastTime = steady_clock::now();														// Lasttime as current for later reference
	}
	
	Mix_Chunk* GetExplSound(){
		static Mix_Chunk* m_pExplSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/explosion.wav");
		Mix_VolumeChunk(m_pExplSound, 50);
		return m_pExplSound;
	}

	Mix_Chunk* GetShieldSound() {
		static Mix_Chunk* m_pShieldSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/shield.wav");
		Mix_VolumeChunk(m_pShieldSound, 50);
		return m_pShieldSound;
	}

	Bullet(double dX, double dY) {
		m_rSrc.x = m_rSrc.y = 0;																// Default positioning
		m_rSrc.w = m_rSrc.h = m_rDst.w = m_rDst.h = 32;											// Default height/width
		m_lastTime = steady_clock::now();														// Lasttime as current for later reference
		m_Dx = dX;
		m_Dy = dY;
	}
	// Bullet update
	void Update(SDL_Renderer* m_pRenderer, Spaceship& s, vector<Enemies*> &e, vector<Explosion*> &expl, int noOfEnemies, int& playerScore, int& numberOfShipsHit, float& kills)
	{
		if (m_bKillMeNow)																		// If bullet is marked for deletion, no need to process the update
			return;
		int cenX, cenY;																			// Center position trackers
		m_rDst.x += 0;																			// No movement in X coordinates. Bullet is movement straight upwards/downwards as of now. Hence X changes not required
		
		if (playerOwned == false) 
		{	
			m_rDst.x += (int)(m_Dx * 2);
			m_rDst.y += (int)(m_Dy * 2);														// Bullet movement with respect to Y coordinates, using the speed and delta change (For enemy bullets)
		}
		else {
			m_rDst.x += (int)(m_Dx * 2);
			m_rDst.y -= (int)(m_Dy * 2);														// Bullet movement with respect to Y coordinates, using the speed and delta change (For player bullets)
		}
			

		m_thisTime = steady_clock::now();														// Get current time, will be referenced against previous time stored in lasttime variable
		duration<double> dur = m_thisTime - m_lastTime;											// Get the duration between the time when bullet was fired and current time
		m_dElapsed += 1 / 60.0f; //dur.count();																// Get the duration in integer form
		m_lastTime = m_thisTime;																// Get the new time for later reference
		if (m_dElapsed >= this->m_dLifespan)													// If elapsed time is greater than the bullet lifespan
			m_bKillMeNow = true;																// Mark the bullet to be removed
	

		// Bullet collision logic for player's bullets
		if (playerOwned) {
			// Logic for bullet collision with enemies
			for (int i = 0; i < e.size(); i++) {												// Bullet collision will be checked against all the enemies present on the map
				cenX = e[i]->m_rDst.x + e[i]->m_rDst.w / 2;										// Center location of the enemy sprite. X Coordinate
				cenY = e[i]->m_rDst.y + e[i]->m_rDst.h / 2;	
				int bcenX = m_rDst.x + m_rDst.w / 2;											// Center location of the enemy sprite. X Coordinate
				int bcenY;
				if (e[i]->enemyType == 3)
					bcenY = (m_rDst.y + m_rDst.h / 2) + 155;									// Center location of the enemy sprite. Y Coordinate
				else
					bcenY = (m_rDst.y + m_rDst.h / 2);
				// enemy = 60x60 / 2 = 30. Bullet = 32

				// If the calculated center falls within the range of bullet, Hit confirmed
				//if (abs(m_rDst.x - cenX) <= 20 && abs(m_rDst.y - cenY) <= 20) {
				//if ((m_rDst.x - cenX) <= 20 && abs(m_rDst.y - cenY) <= 20) {
				if (((bcenX - e[i]->m_rDst.x) >= 10 && (bcenY - e[i]->m_rDst.y) >= 10) && (bcenX - e[i]->m_rDst.x - e[i]->m_rDst.w) <= -10 && (bcenY - e[i]->m_rDst.y - e[i]->m_rDst.h) <= -10) {
					Explosion* exp = new Explosion(e[i]->m_rDst.x, e[i]->m_rDst.y);//e[i]->m_rDst.x + e[i]->m_rDst.w / 2, e[i]->m_rDst.y + e[i]->m_rDst.h / 2);
					expl.push_back(exp);
					cout << "Expl Size: " << expl.capacity() << endl;
					// play the explosion sound effect
					/*Mix_Chunk* m_pExplSound;
					m_pExplSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/explosion.wav");*/
					Mix_PlayChannel(-1, GetExplSound(), 0);										// Play the explosion sound

					if (e[i]->enemyHealth <= 1)
					{
						if (e[i]->gridIndex) {
							//e[i]->gridIndex->isLocked = false;											// Open up the grid location
							for (int i = 0; i < Scene::grid.size(); i++)
							{
								/*if (Scene::grid[i] != NULL) {
									if (Scene::grid[i].gridX == e[i]->gridIndex->gridX &&
										Scene::grid[i].gridY == e[i]->gridIndex->gridY)
										Scene::grid[i].isLocked = false; 
								}*/
								
							}
						}
						Enemies* temp = e[i];
						if (temp->enemyType == 4) {
							for (int k = 0; k < e.size(); k++)
							{
								if (e[k]->enemyType == 3)
									e[k]->enemyHealth -= 10;
							}
						}
						e[i]->Cleanup();
						for (int j = 0; j < e.size(); j++)
						{
							if ((e[j]) == temp) {
								delete e[j];																// Delete enemy allocated space
								e[j] = nullptr;
								e.erase(e.begin() + j);														// remove that enemy from the vector list
								e.shrink_to_fit();
							}
						}
					}
					else
					{
						e[i]->enemyHealth--;
					}
					kills++;
					Bullet::m_iScore += 100;													// Add to the score if the player kills an enemy
					Bullet::m_iCurrentScore += 100;
					numberOfShipsHit++;															// Add to the total number of enemies killed
					cout << "SCORE: " << Bullet::m_iScore << endl;								// Chris: Debug - This line is for testing
					m_bKillMeNow = true;														// Mark the bullet for removal.
				}
			}
		}
		else {
			cenX = s.m_rDst.x + s.m_rDst.w / 2;													// Center location of the enemy sprite. X Coordinate
			cenY = s.m_rDst.y + s.m_rDst.h / 2;													// Center location of the enemy sprite. Y Coordinate
			// If the calculated center falls within the range of bullet, Hit confirmed
			// Check if player is in respawning animation or not, if it is, bullets should not hit until the completion of respawning animation
			if (!Timer::m_bTimerNeeded) {
				if (abs(m_rDst.x - cenX) <= 20 && abs(m_rDst.y - cenY) <= 20) {
					Explosion* exp = new Explosion(s.m_rDst.x, s.m_rDst.y);//e[i]->m_rDst.x + e[i]->m_rDst.w / 2, e[i]->m_rDst.y + e[i]->m_rDst.h / 2);
					expl.push_back(exp);

					// play the explosion sound effect
					//Mix_Chunk* m_pExplSound;
					//m_pExplSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/explosion.wav");
					Mix_PlayChannel(-1, GetExplSound(), 0);											// Play the explosion sound

					m_bKillMeNow = true;															// Mark the bullet for removal.
					if(!s.godMode)
					if (!(m_iLives <= 0)) {
						if (!s.powerUpCharges[3])
						{
							m_iLives--;
							// Set the timer requirements
							Timer::m_bTimerNeeded = true;												// Player got hit. Set the timer so that we can render the blinking effect
																										// Get initial time
							Timer::m_iStartTick = SDL_GetTicks();
						}
						if (s.powerUpCharges[3])
						{
							s.powerUpCharges[3] = 0;
							Mix_PlayChannel(-1, GetShieldSound(), 0);
						}
					}
				}
			}
		}
	}
	const SDL_Rect* GetSrc() { return &m_rSrc; }												// Get the source rectangle
	const SDL_Rect* GetDst() { return &m_rDst; }												// Get the destination rectangle
};

class Lazer : public Bullet
{
private:
	SDL_Rect hitBox;

public:
	Lazer(Spaceship &s)
	{
		m_rDst.x = s.m_rDst.x;
		m_rDst.y = s.m_rDst.y - 768 + 10;
		m_rDst.w = 95;
		m_rDst.h = 768;
		m_rSrc = { 0, 0, 272, 2185 };
		hitBox.x = m_rDst.x + 7;
		hitBox.y = m_rDst.y;
		hitBox.h = m_rDst.h;
		hitBox.w = 70;

		this->m_dLifespan = 1;
		m_lastTime = steady_clock::now();
	}

	void Update(Spaceship &s, vector<Enemies*> &e, int& playerScore, int& numberOfShipsHit, float& kills, vector<Explosion*> &expl)
	{
		m_rDst.x = s.m_rDst.x - 20;
		hitBox.x = s.m_rDst.x - 5;
		hitBox.y = s.m_rDst.y - 768 + 10;
		m_rDst.y = s.m_rDst.y - 768 + 10;

		m_thisTime = steady_clock::now();
		duration<double> dur = m_thisTime - m_lastTime;
		m_dElapsed += dur.count();
		m_lastTime = m_thisTime;
		if (m_dElapsed >= this->m_dLifespan)
		{
			m_bKillMeNow = true;
		}
		int max = e.size();
		for (int i = 0; i < max; i++)
		{
			max = e.size();
			if (max == 0) return;
			if (SDL_HasIntersection(&hitBox, &(e[i]->m_rDst)))
			{
				if (e[i]->enemyHealth < 1)
				{
					Enemies* temp = e[i];
					e[i]->Cleanup();
					for (int j = 0; j < e.size(); j++)
					{
						if (temp == e[j]) i = j;
					}
					if(i < e.size()){
						delete e[i];																// Delete enemy allocated space
						e[i] = nullptr;
						e.erase(e.begin() + i);														// remove that enemy from the vector list
						e.shrink_to_fit();
					}
					i = 0;			// MOVES INDEX BACK TO START
					max = e.size();
					//Explosion* exp = new Explosion(e[i]->m_rDst.x, e[i]->m_rDst.y);//e[i]->m_rDst.x + e[i]->m_rDst.w / 2, e[i]->m_rDst.y + e[i]->m_rDst.h / 2);
					//expl.push_back(exp);

					//// play the explosion sound effect
					////Mix_Chunk* m_pExplSound;
					////m_pExplSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/explosion.wav");
					//Mix_PlayChannel(-1, GetExplSound(), 0);											// Play the explosion sound
				}
				else
				{
					e[i]->enemyHealth--;
				}
				kills++;
				Bullet::m_iScore += 100;													// Add to the score if the player kills an enemy
				Bullet::m_iCurrentScore += 100;
				numberOfShipsHit++;															// Add to the total number of enemies killed
				cout << "SCORE: " << Bullet::m_iScore << endl;								// Chris: Debug - This line is for testing
			}
		}
	}
};