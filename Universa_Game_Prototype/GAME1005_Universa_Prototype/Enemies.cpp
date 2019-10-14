/**********************************
Filename: Enemies.cpp
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 07/02/2019
***********************************/

#include "stdafx.h"
#include "Enemies.h"
#include <Windows.h>
#include "Transform.h"
#include "MoveBehaviour.h"
#include "Game.h"
#include "PathFollowing.h"

/* 
Dimensions calculation (Individual Enemy):
Left - 17
right - 18
width: 87
height: 118
*/

// Enemies spawn location offset. 
// X and Y coordinates update to make sure that each enemy has their own unique spot. 
int Enemies::offsetX = 5;
int Enemies::offsetY = 10;

// Update the destination rectangle for enemy's location coordinates
void Enemies::UpdateDest() {
	m_rDst.x = m_x;
	m_rDst.y = m_y;
}

void Enemies::Update()
{
	alienBehaviour->Update(); // ?? Does it work ?? Trying to skip SteeringBehaviour update(), if it doesnt call it and call MoveBehaviour() from inside steering
}

// Enemies constructor.
// Sets the basic speed of object's movement.  
// Sets location coordinates to (0, 0)
// Sets height and width (Source and Destination Rect.) according to the size of the enemy texture.

Enemies::Enemies() {
	canFire = false;//	canFire = true;
	m_iSpeed = 2;
	m_rSrc.x = m_rSrc.y = 0;
	m_rSrc.w = m_rDst.w = 60;//120;
	m_rSrc.h = m_rDst.h = 60;//118;
	
	// If the current X coordinate points above 950, first row has been filled with enemies,
	// proceed to next row by changing the Y coordinate.
	if ((m_x + offsetX) > 950) {	
		m_x = 50;																						// Enemy location x coordinate change to default.
		offsetX = 5;																					// Offset reset to default
		m_x += offsetX;																					// Add offset to current X coordinate to move to next available location in new row
		offsetY += 50;																					// Add value to Y offset, changes the row
		m_y += offsetY;																					// Add the offset value to Y coordinate of enemy location
	}
	else {
		m_x += offsetX;																					// If rendering location is still within the boundaries,
		m_y += offsetY;																					// then change X and Y using offset values to go to next location for next enemy's texture rendering
	}
	offsetX += m_rSrc.w + 5;																			// X offset needs to consider width of source rectangle + additional offset to allow enough space between two enemies.
	
	UpdateDest();																						// Update the destination location 
	transform = new Transform(m_x, m_y, 0.0f, 0.0f, 0.0f);
	MoveBehaviour* moveBehav = new MoveBehaviour(this);
	alienBehaviour = moveBehav;
	alienBehaviour->maxSpeed = 80;
}

Enemies::~Enemies()
{
	Cleanup();
}

void Enemies::Cleanup()
{
	delete transform;
	transform = nullptr;
	delete alienBehaviour;
	alienBehaviour = nullptr;
}

void Enemies::SwitchMove(MoveType newMove)
{
	delete alienBehaviour;
	alienBehaviour = nullptr;
	//if(newMove == MoveType::Standard)
		alienBehaviour = new MoveBehaviour(this);
	/*else 
		alienBehaviour = new PathFollowing(this);*/
	alienBehaviour->maxSpeed = 400;
	canFire = true;
}

// Parameterized constructor
// Allows to make enemies spawn at different - user specified location
Enemies::Enemies(int posX, int posY, int p_iType) {
	canFire = false;//	canFire = true;
	if (p_iType == 4) canFire = true;
	enemyType = p_iType;
	if (enemyType == 1)
	{
		enemyHealth = 1;
	}
	else if (enemyType == 2)
	{
		enemyHealth = 2;
	}
	else if (enemyType == 4)
	{
		enemyHealth = 10;
	}

	//m_x += posX;																						// Change x coordinate
	//m_y += posY;																						// Change y coordinate
	m_iSpeed = 2;																						// Movement speed
	m_rSrc.x = m_rSrc.y = 0;																			// Default location
	m_rSrc.w = m_rDst.w = 60;																			// Default width - Source and Destination rectangle
	m_rSrc.h = m_rDst.h = 60;																			// Default height - Source and Destination rectangle
	m_x = posX;
	m_y = posY;

	UpdateDest();																						// Update the destination location
	transform = new Transform(m_x, m_y, 0.0f, 0.0f, 0.0f);
	alienBehaviour = new MoveBehaviour(this);
	alienBehaviour->maxSpeed = 80;
}

Enemies::Enemies(int p_iType) {
	canFire = false;//	canFire = true;
	enemyType = p_iType;
	if (enemyType == 1)
	{
		enemyHealth = 1;
	}
	else if (enemyType == 2)
	{
		enemyHealth = 2;
	}
	else if (enemyType == 4)
	{
		enemyHealth = 10;
	}

	m_iSpeed = 2;																						// Movement speed
	m_rSrc.x = m_rSrc.y = 0;																			// Default location
	m_rSrc.w = m_rDst.w = 60;																			// Default width - Source and Destination rectangle
	m_rSrc.h = m_rDst.h = 60;																			// Default height - Source and Destination rectangle

	// If the current X coordinate points above 950, first row has been filled with enemies,
	// proceed to next row by changing the Y coordinate.
	if ((m_x + offsetX) > 950) {
		m_x = 50;																						// Enemy location x coordinate change to default.
		offsetX = 5;																					// Offset reset to default
		m_x += offsetX;																					// Add offset to current X coordinate to move to next available location in new row
		offsetY += 50;																					// Add value to Y offset, changes the row
		m_y += offsetY;																					// Add the offset value to Y coordinate of enemy location
	}
	else {
		m_x += offsetX;																					// If rendering location is still within the boundaries,
		m_y += offsetY;																					// then change X and Y using offset values to go to next location for next enemy's texture rendering
	}
	offsetX += m_rSrc.w + 5;																			// X offset needs to consider width of source rectangle + additional offset to allow enough space between two enemies.

	UpdateDest();																						// Update the destination location 
	transform = new Transform(m_x, m_y, 0.0f, 0.0f, 0.0f);
	MoveBehaviour* moveBehav = new MoveBehaviour(this);
	alienBehaviour = moveBehav;
	alienBehaviour->maxSpeed = 80;

}

// Get the source rectangle
const SDL_Rect* Enemies::GetSrc() {
	return &m_rSrc;
}

// Get the destination rectangle
// Usually needed to pinpoint object's location after rendering on the screen
const SDL_Rect* Enemies::GetDst() {
	m_rDst.x = transform->position.x - (m_rDst.w/2);
	m_rDst.y = transform->position.y - (m_rDst.h/2);
	return &m_rDst;
}

void Enemies::ResetStats() {
	Enemies::offsetX = 5;
	Enemies::offsetY = 10;
	m_x = m_y = 50;
	m_rSrc.x = m_rSrc.y = 0;																			// Default location
	m_rSrc.w = m_rDst.w = 60;																			// Default width - Source and Destination rectangle
	m_rSrc.h = m_rDst.h = 60;																			// Default height - Source and Destination rectangle
}

// Change frames according to object's movement
void Enemies::AdvanceAnim() {
	// Advance animation for type 1.
	if (enemyType == 1) {
		if (counter > 10) {																				// Counter to slow down animation speed (Enemy object framerate capping)
			counter = 0;																				// If the counter reaches predefined number, reset
			m_iFrameCtr++;																				// Increase the frame counter
			if (m_iFrameCtr == m_iFrameMax)																// If the frame counter reaches maximum, reset
				m_iFrameCtr = 0;																		// Frame counter for frames in the sprite
			m_rSrc.x = 60 * m_iFrameCtr;																// Advance the frame to next in line
		}
		else {
			counter++;																					// Counter to slow down animation speed (Enemy object framerate capping)
		}
	}
	// Advance animation for type 2
	else {
		if (counter > 10) {																				// Counter to slow down animation speed (Enemy object framerate capping)
			counter = 0;																				// If the counter reaches predefined number, reset
			m_iFrameCtr++;																				// Increase the frame counter
			if (m_iFrameCtr == m_iFrameMax2)															// If the frame counter reaches maximum, reset
				m_iFrameCtr = 0;																		// Frame counter for frames in the sprite
			m_rSrc.x = 60 * m_iFrameCtr;																// Advance the frame to next in line
		}
		else {
			counter++;																					// Counter to slow down animation speed (Enemy object framerate capping)
		}
	}
}

// Change frames according to object's idle position
// Example: There are 9 frames to create enemy type 1
// There are 5 frames to create enemy type 2
void Enemies::SetIdle() {
	if (enemyType == 1) {
		if (counter > 10) {																				// Counter to slow down animation speed (Enemy object framerate capping)
			counter = 0;
			m_iFrameCtr++;
			if (m_iFrameCtr == m_iFrameMax)
				m_iFrameCtr = 0;
			m_rSrc.x = 60 * m_iFrameCtr;
		}
		else {
			counter++;
		}
	}
	else if (enemyType == 2) {
		if (counter > 10) {																				// Counter to slow down animation speed (Enemy object framerate capping)
			counter = 0;
			m_iFrameCtr++;
			if (m_iFrameCtr == m_iFrameMax2)
				m_iFrameCtr = 0;
			m_rSrc.x = 60 * m_iFrameCtr;
		}
		else {
			counter++;
		}
	}
}

Boss::Boss(Game * g, int p_iType): Enemies()
{
	canFire = false;
	gPtr = g;
	enemyType = p_iType;
	if (enemyType == 3)
	{
		enemyHealth = 100;
	}
	m_bWeaponActive = false;
	
	m_rSrc.w = m_rDst.w = 566, m_rSrc.h = m_rDst.h = 511, enemyType = 3, m_iFrameMax = 0, m_iFrameMax2 = 0;
	bosspart1 = new Enemies(335,225,4), bosspart2 = new Enemies(510,355,4), bosspart3 = new Enemies(690,225,4);
	g->GetFSM()->getEnemies()->push_back(bosspart1);
	g->GetFSM()->getEnemies()->push_back(bosspart2);
	g->GetFSM()->getEnemies()->push_back(bosspart3);
	
}

Boss::~Boss() {
	
}

void Boss::Cleanup() {
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < (*gPtr->GetFSM()->getEnemies()).size(); i++)
		{
			if ((*gPtr->GetFSM()->getEnemies())[i]->enemyType == 4) {
				(*gPtr->GetFSM()->getEnemies())[i]->Cleanup();
				delete (*gPtr->GetFSM()->getEnemies())[i];																// Delete enemy allocated space
				(*gPtr->GetFSM()->getEnemies())[i] = nullptr;
				(*gPtr->GetFSM()->getEnemies()).erase((*gPtr->GetFSM()->getEnemies()).begin() + i);														// remove that enemy from the vector list
				//(*gPtr->GetFSM()->getEnemies()).shrink_to_fit();
			}

		}
	}
	
	bosspart1 = nullptr;
	bosspart2 = nullptr;
	bosspart3 = nullptr;
	Enemies::Cleanup();
}

Enemies::Enemies( int p_iType, bool b, Vector2 vec, Scene::gridLocation* gIndex, Vector2 vecOffset) {
	canFire = false;//	canFire = true;
	gridIndex = gIndex;
	enemyType = p_iType;
	if (enemyType == 1)
	{
		enemyHealth = 1;
	}
	else if (enemyType == 2)
	{
		enemyHealth = 2;
	}
	else if (enemyType == 4)
	{
		enemyHealth = 10;
	}

	int x = rand() % 2;
	alienBehaviour = new PathFollowing(this, x, vec, vecOffset);
	PathFollowing* pf = dynamic_cast<PathFollowing*>(alienBehaviour);

	//m_x += posX;																						// Change x coordinate
	//m_y += posY;																						// Change y coordinate
	m_iSpeed = 2;																						// Movement speed
	m_rSrc.x = m_rSrc.y = 0;																			// Default location
	m_rSrc.w = m_rDst.w = 60;																			// Default width - Source and Destination rectangle
	m_rSrc.h = m_rDst.h = 60;																			// Default height - Source and Destination rectangle
	if (x == 0) {
		m_x = pf->waypoints.front().x;
		m_y = pf->waypoints.front().y;
	}
	else {
		m_x = pf->waypoints.front().x;
		m_y = pf->waypoints.front().y;
	}
	
	UpdateDest();																						// Update the destination location
	transform = new Transform(m_x, m_y, 0.0f, 0.0f, 0.0f);
	pf->Start();
	//alienBehaviour = new MoveBehaviour(this);
	//alienBehaviour->maxSpeed = 80;

}
