/**********************************
Filename: Spaceship.cpp
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 26/01/2019
***********************************/

#include "stdafx.h"
#include "Spaceship.h"
#include <Windows.h>

// Spaceship (player) object location update
void Spaceship::UpdateDest() {
	m_rDst.x = m_x;
	m_rDst.y = m_y;
	AdvanceAnim();
}

// Spaceship constructor
Spaceship::Spaceship() {
	powerUpCharges.push_back(0);
	powerUpCharges.push_back(0);
	powerUpCharges.push_back(0);
	powerUpCharges.push_back(0);
	m_x = 1024 / 2;																						// Initial position (X coordinate), near bottom of the screen
	m_y = 670;																							// Initial position (Y coordinate), center on the horizontal line
	m_iSpeed = 6;																						// Initial player object movement speed
	m_rSrc.x = m_rSrc.y = 0;																			// Source rectangle location - set to default
	m_rSrc.w = m_rDst.w = 60;																			// Width of source and destination rectangles to render the object image
	m_rSrc.h = m_rDst.h = 60;																			// Height of the source and destination rectangles
	UpdateDest();																						// Update the location with default location setup
}

// Move player object on X axis
void Spaceship::MoveX(int p_iM) {
	this->m_x += p_iM * m_iSpeed;																		// Player object's X coordinate will be changed according to the speed * movement offset
	//if(this->m_x > 0 && this->m_x < 1000)																// Screen boundry check
	UpdateDest();																						// Update player object's location after coodinate changes
}

// Move player object on Y axis
void Spaceship::MoveY(int p_iM) {
	this->m_y += p_iM * m_iSpeed;																		// Player object's Y coordinate will be changed according to the speed * movement offset
	//if(this->m_y > 0 && this->m_y < 700)																// Screen boundry check
	UpdateDest();																						// Update player object's  location after coordinate changes
}

// Getter for the source rectangle 
const SDL_Rect* Spaceship::GetSrc() {
	return &m_rSrc;
}

// Getter for the destination rectangle
const SDL_Rect* Spaceship::GetDst() {
	return &m_rDst;
}

// Advance the player sprite animation
void Spaceship::AdvanceAnim() {
	if (counter > 20) {																					// Counter to cap the animation speed
		counter = 0;																					// If counter reaches predefined point, reset it and allow the player sprite animation to move further.
		m_iFrameCtr++;
		if (m_iFrameCtr == m_iFrameMax)
			m_iFrameCtr = 0;																			// Frame counter for frames in the sprite
		m_rSrc.x = 60 * m_iFrameCtr;																	// Advance the frame to next in line
	}
	else {
		counter++;																						// Else, just update the counter. No sprite change
	}
}

// Player sprite animation in idle state
void Spaceship::SetIdle() {
	if (counter > 20) {																					// Counter to cap the animation speed
		counter = 0;																					// If counter reaches predefined point, reset it and allow the player sprite animation to move further.
		m_iFrameCtr++;
		if (m_iFrameCtr == m_iFrameMax)
			m_iFrameCtr = 0;																			// Frame counter for frames in the sprite
		m_rSrc.x = 60 * m_iFrameCtr;																	// Advance the frame to next in line
	}
	else {
		counter++;																						// Else, just update the counter. No sprite change
	}
}