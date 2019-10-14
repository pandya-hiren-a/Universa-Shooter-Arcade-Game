/**********************************
Filename: Spaceship.h
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 26/01/2019
***********************************/
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class Spaceship {
	void UpdateDest();			// Update destination rectangle positioning
public:
	int counter = 0;			// Counter to cap the animation speed
	int m_x;					// Player's location - X coordinate
	int m_y;					// Player's location - Y coordinate
	int m_iSpeed;				// Player object's movement speed
	int m_iFrameCtr = 0;		// Player object's initial frame
	int m_iFrameMax = 7;		// Player object's maximum frame number
	bool m_bRight = true;		// If player is turning right
	SDL_Rect m_rSrc;			// Source rectangle
	SDL_Rect m_rDst;			// Destination rectangle
	std::vector<int> powerUpCharges;
	bool godMode = false;

	Spaceship();				// Spaceship constructor
	void MoveX(int);			// Player movement on X axis
	void MoveY(int);			// Player movement on Y axis
	const SDL_Rect* GetSrc();	// Getter for source rectangle 
	const SDL_Rect* GetDst();	// Getter for destination rectangle
	void AdvanceAnim();			// Animate while moving
	void SetIdle();				// Animate while idle
};