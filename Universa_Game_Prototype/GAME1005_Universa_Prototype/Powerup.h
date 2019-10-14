/**********************************
Filename: Powerup.h
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

using namespace std;
using namespace chrono;

class Powerup {
public:
	Game* gamePtr;
	SDL_Rect m_rSrc;																			// Source rectangle to facilitate rendering
	SDL_Rect m_rDst;																			// Destination rectangle to facilitate rendering 

	static int m_iPowerupSpeed;																	// Powerup movement speed. Only one instance of this is created ever. 
	static double m_dLifespan;																	// Powerup lifespan after it has been fired

	bool m_bKillMeNow = false;																	// If Powerup should be removed from the render screen
	double m_Dx;																				// Delta for X coordinate movement
	double m_Dy;																				// Delta for Y coordinate movement
	double m_dElapsed = 0.0;																	// Time counter to count passed moments after the Powerup has been fired
	bool playerOwned = false;																	// To check if the Powerup has been fired by the player
	bool active = false;
	bool shieldActive = false;

	enum poweruptypes {Multishot, Laser, Bomb, Shield};											// Multi = 0, Laser = 1, Bomb = 2, Shield = 3
	int poweruptype;

	steady_clock::time_point m_lastTime;														// Last update time to confirm Powerup lifespan
	steady_clock::time_point m_thisTime;														// Current time to confirm Powerup lifespan

	// Powerup constructor
	Powerup()
	{
		m_rSrc.x = m_rSrc.y = 0;																// Default positioning
		m_rSrc.w = m_rSrc.h = m_rDst.w = m_rDst.h = 32;											// Default height/width
		m_lastTime = steady_clock::now();														// Lasttime as current for later reference
		m_Dx = m_Dy = 0;

		poweruptype = rand() % 4;
	}

	/*Mix_Chunk* GetExplSound() {
		static Mix_Chunk* m_pExplSound = (Mix_Chunk*)Mix_LoadWAV("./assets/audio/effects/explosion.wav");
		return m_pExplSound;
	}*/
	Powerup(double dX, double dY) {
		m_rSrc.x = m_rSrc.y = 0;																// Default positioning
		m_rSrc.w = m_rSrc.h = m_rDst.w = m_rDst.h = 32;											// Default height/width
		m_lastTime = steady_clock::now();														// Lasttime as current for later reference
		m_Dx = dX;
		m_Dy = dY;

		poweruptype = rand() % 4;
	}

	// Powerup update
	void Update(SDL_Renderer* m_pRenderer, Spaceship& s, vector<Enemies*> &e)
	{
		if (m_bKillMeNow)																		// If Powerup is marked for deletion, no need to process the update
			return;
		int cenX, cenY;																			// Center position trackers
		m_rDst.x += 0;																			// No movement in X coordinates. Powerup is movement straight upwards/downwards as of now. Hence X changes not required
		
		if (playerOwned == false) {

			m_rDst.y += (int)(m_Dy * Powerup::m_iPowerupSpeed);									// Powerup movement with respect to Y coordinates, using the speed and delta change (For enemy Powerups)
		}
		else {
			m_rDst.x += (int)(m_Dx * 2);
			m_rDst.y -= (int)(m_Dy * Powerup::m_iPowerupSpeed);									// Powerup movement with respect to Y coordinates, using the speed and delta change (For player Powerups)
		}


		m_thisTime = steady_clock::now();														// Get current time, will be referenced against previous time stored in lasttime variable
		duration<double> dur = m_thisTime - m_lastTime;											// Get the duration between the time when Powerup was fired and current time
		m_dElapsed += dur.count();																// Get the duration in integer form
		m_lastTime = m_thisTime;																// Get the new time for later reference
		if (m_dElapsed >= this->m_dLifespan)													// If elapsed time is greater than the Powerup lifespan
			m_bKillMeNow = true;																// Mark the Powerup to be removed

		 {
			cenX = s.m_rDst.x + s.m_rDst.w / 2;													// Center location of the enemy sprite. X Coordinate
			cenY = s.m_rDst.y + s.m_rDst.h / 2;													// Center location of the enemy sprite. Y Coordinate
			// If the calculated center falls within the range of Powerup, pickup confirmed
			if (abs(m_rDst.x - cenX) <= 40 && abs(m_rDst.y - cenY) <= 40) {
				//Mix_PlayChannel(-1, GetExplSound(), 0);										// Play the explosion sound

				//Powerup* powerup = new Powerup(e[i]->m_rDst.x, e[i]->m_rDst.y);
				//m_rDst.y += (int)(m_Dy * 2);

				m_bKillMeNow = true;															// Mark the Powerup for removal.
				s.powerUpCharges[poweruptype] += 10;
				active = true;
			}
		}
	}
	const SDL_Rect* GetSrc() { return &m_rSrc; }												// Get the source rectangle
	const SDL_Rect* GetDst() { return &m_rDst; }												// Get the destination rectangle)
};