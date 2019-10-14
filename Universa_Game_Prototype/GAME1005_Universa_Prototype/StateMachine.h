#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "Path.h"

using namespace std;

class Bullet;
class Spaceship;
class Enemies;
class Button;
class Game;
class Levels;
class Scene;
class State
{
protected:
	

public:
	Game* gamePtr;
	Scene* currentScene = nullptr;
	bool popState = false;
	int score;
	virtual void update(Spaceship&, vector<Enemies*>&) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void resume() = 0;

	virtual void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);

	State(Game*);
	~State();
};

class TitleState : public State
{
private:
	SDL_Texture * highscoreText;
	SDL_Texture * highscoreText2;

	SDL_Surface* m_pSurf;
	SDL_Texture* m_pText;
	SDL_Texture* m_pText2;

	SDL_Rect grayBoxDst = { 100, 762 / 2 - 200, 824, 350 };
	SDL_Rect grayBoxSrc = { 0, 0, 824, 400};

	SDL_Rect ttfRect[12];
	SDL_Rect ttfDest[12];

	SDL_Rect ttfRect2[12];
	SDL_Rect ttfDest2[12];

	SDL_Texture* ttfText[12];
	SDL_Texture* ttfCredits[12];
	SDL_Rect temp;
	SDL_Rect highScoresTextDst = { 450, 63, 520, 100 };
	SDL_Rect highScoresTextSrc = { 0, 0, 1300, 250 };

	bool highScores = false;
	bool credits = false;
	bool controls = false;

	vector<Mix_Music*> music;
	vector<Button*> m_vButtons;
	SDL_Texture* buttonText;
	enum btn { NEWGAME, HIGHSCORES, EXITGAME, CONTROLS, CREDITS, MAINMENU};


public:
	TitleState(Game* gptr) : State(gptr) {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);
	void enter();
	void exit();
	void resume();
	void setHighScoreState(bool o) { highScores = o; }
	bool getHighScoreState() { return highScores; }
};

class GameState : public State
{
private:
	SDL_Rect src = { 0, 0, 1024, 3072 };
	SDL_Rect dst = { 0, -3072 + 768, 1024, 3072 };
	SDL_Rect dst2 = { 0, -3072*2 + 768, 1024, 3072 };

	SDL_Rect shieldSrc = { 0, 0, 300, 300 };
	SDL_Rect srcTriple = { 0, 0, 32, 32 };
	SDL_Rect dstTriple = { 888, 660, 32, 32 };
	SDL_Rect srcLife = { 0, 0, 50, 50 };
	SDL_Rect dstLife1 = { 880, 700, 40, 40 };
	SDL_Rect dstLife2 = { 925, 700, 40, 40 };
	SDL_Rect dstLife3 = { 970, 700, 40, 40 };

	SDL_Rect bossSrc = { 0, 0, 943, 80 };
	SDL_Rect bossDst = { 50, 10, 943, 80 };

	bool shield = false;
	bool initialEnter = false;
	bool m_bPlayerVisible = true;
	bool level5 = false;
	float runTime;
	float numberOfShots;
	float kills;


	
public:
	GameState(Game* gptr) : State(gptr) {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game*, Spaceship&, vector<Enemies*>&);
	void enter();
	void exit();
	void resume();

	void SetScene(Scene*);
	
};

class PauseState : public State
{
private:
	SDL_Surface* m_pSurf;
	SDL_Texture* m_pText;
	vector<Button*> m_vButtons;
	SDL_Texture* buttonText;
	enum btn { RESUME, MAINMENU };
public:
	PauseState(Game* gptr) : State(gptr) {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);
	void enter();
	void exit();
	void resume();
};

class WinState : public State
{
private:
	SDL_Surface* m_pSurf;
	SDL_Texture* m_pText;
	SDL_Texture* highscoreText;
	SDL_Rect temp;
	vector<Button*> m_vButtons;
	SDL_Texture* buttonText;
	enum btn { PLAYAGAIN, MAINMENU };
public:
	WinState(Game* gptr) : State(gptr) {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);
	void enter();
	void exit();
	void resume();

	void SetScene(Scene*);
};

class LossState : public State
{
private:
	SDL_Surface* m_pSurf;
	SDL_Texture* m_pText;

	vector<Button*> m_vButtons;
	SDL_Texture* buttonText;
	enum btn { PLAYAGAIN, MAINMENU };
public:
	LossState(Game* gptr) : State(gptr) {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);
	void enter();
	void exit();
	void resume();
};

class StateMachine
{
private:
	vector<State*> m_vStates;
	vector<Enemies*>* enemies;
	
public:
	StateMachine() {}
	void update(Spaceship& s, vector<Enemies*>& e);
	void render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e);
	void pushState(State* state);
	void changeState(State* state);
	void popState();
	void popState(int);
	void clean();

	vector<State*> getState()
	{
		return m_vStates;
	}
	vector<Enemies*>* getEnemies()
	{
		return enemies;
	}

	int stateSize()
	{
		return m_vStates.size();
	}
};