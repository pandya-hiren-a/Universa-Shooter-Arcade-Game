/**********************************
Filename: Explosion.h
Author: F-Racing Team
Created On: 07/02/2019
Modified On: 07/02/2019
***********************************/
#pragma once
#include <chrono>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Enemies.h"
#include "Spaceship.h"
#include <cmath>

class Explosion {
public:
	bool m_bFinished;													// Indicates completion of explosion process
	SDL_Rect m_rSrc;													// Source rectangle to facilitate rendering
	SDL_Rect m_rDst;													// Destination rectangle to facilitate rendering 
	int counter;														// Frame-rate capping 

	Explosion() {
		// IF explosion object created along with only renderer
		m_rSrc.x = m_rSrc.y = 0;										// Set default position of source rectangle for image sprite
		m_rDst.h = m_rDst.w = m_rSrc.h = m_rSrc.w = 60;					// Set all the widths and heights to 60
	}

	// Parameterised constructor
	Explosion(int xPos, int yPos) {
		// If explosion is suppose to happen at a specific location			 
		m_rSrc.x = m_rSrc.y = 0;
		m_rDst.x = xPos;													// Set the x coordinate for explosion position
		m_rDst.y = yPos;													// Set the y coordinate for explosion position
		m_rDst.h = m_rDst.w = m_rSrc.h = m_rSrc.w = 60;						// Set default heights and widths
		counter = 0;														// Set the initial value for frame-rate limiter
		m_bFinished = false;
	}

	~Explosion() {
	}

	// Update the frame for next sprite
	void update() {
		if (counter < 5) {
			counter++;
			return;
		}
		else
			counter = 0;
		if (m_rSrc.x < 1020)	// If we haven't reached at the end of the sprite, continue increasing 
			m_rSrc.x += 60;
		else
			m_bFinished = true; // If we reached at the end of the sprite, mark it as complete for later deletion
	}
};