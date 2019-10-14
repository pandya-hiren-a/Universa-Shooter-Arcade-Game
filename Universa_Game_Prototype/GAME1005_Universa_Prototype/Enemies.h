/**********************************
Filename: Enemies.h
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 07/02/2019
***********************************/
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Transform.h"
#include "SteeringBehaviour.h"
#include "PathFollowing.h"
#include <vector>
#include "Vector2.h"
#include "Scene.h"

class Enemies {
protected:
	void UpdateDest();
	virtual void Update();
	bool canFire;
public:
	int counter = 0;													// Counter to cap the sprite animation speed
	int m_x = 50;														// Initial X coordinate for location
	int m_y = 50;														// Initial Y coordinate for location
	int m_iSpeed;														// Movement speed
	int m_iFrameCtr = 0;												// Current frame
	int m_iFrameMax = 9;												// Maximum frames
	int m_iFrameMax2 = 5;												// Maximum frames for enemy type 2
	bool m_bRight = true;												// Moving on right
	int enemyType = 1;													// To select between enemy type 1 and enemy type 2
	int enemyHealth = 1;
	SDL_Rect m_rSrc;													// Source Rectangle for rendering purposes
	SDL_Rect m_rDst;													// Destination Rectangle for rendering purposes
	static int offsetX;													// Offset for X coordinate _ Used for enemy positioning while rendering multiple enemies
	static int offsetY;													// Offset for Y coordinate _ Used for enemy positioning while rendering multiple enemies
	bool m_bIsAlive = true;												// Check if enemy's alive or not
	bool m_bWeaponActive = true;
	Scene::gridLocation* gridIndex;										// Index of the grid location utilized by the enemy

	Enemies();															// Enemies Constructor
	~Enemies();
	Enemies(int, int, int);												// Enemies Parameterized constructor
	//Enemies(int, bool);												// Enemies Parameterized constructor
	Enemies(int, bool, Vector2, Scene::gridLocation*, Vector2);			// Enemies Parameterized constructor
	Enemies(int);														// Enemies Parameterized constructor
	const SDL_Rect* GetSrc();											// Getter for source rectangle
	const SDL_Rect* GetDst();											// Getter for destination rectangle
	void ResetStats();													// Reset internal variables
	virtual void AdvanceAnim();											// Animate while moving
	void SetIdle();														// Animate while idle
	Transform* transform;
	SteeringBehaviour* alienBehaviour;
	virtual void Cleanup();
	enum MoveType {PathFollow, Standard};
	void SwitchMove(MoveType);
	bool GetCanFire() const { return canFire; }
};
class Game;
class Boss : public Enemies
{
public:
	Game* gPtr;
	Boss() {}
//	Boss(std::vector<Enemies*>enemylist) :Enemies() 
	//Boss(Game* g);
	Boss(Game* g, int);													// Sets Boss to enemy type 3
	~Boss();
	Enemies* bosspart1;													// Left arm
	Enemies* bosspart2;													// Right arm
	Enemies* bosspart3;													// Middle

	void Cleanup();
	void AdvancAnim() {}
	void Update() { Enemies::Update();  }
};