#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "Game.h"

//class Game;
class Level1 :
	public Scene
{
public:
	Level1(Game*);
	~Level1();

	void Setup();
	void Update();
};

class Level2 :
	public Scene
{
public:
	Level2(Game*);
	~Level2();

	void Setup();
	void Update();
};

class Level3 :
	public Scene
{
public:
	Level3(Game*);
	~Level3();

	void Setup();
	void Update();
};

class Level4 :
	public Scene
{
public:
	Level4(Game*);
	~Level4();

	void Setup();
	void Update();
};

class Level5 :
	public Scene
{
public:
	Level5(Game*);
	~Level5();

	void Setup();
	//void Update();
};