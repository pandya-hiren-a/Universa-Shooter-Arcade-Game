#pragma once
#include "SDL.h"
#include "StateMachine.h"
#include "Game.h"

class Button
{
private:
	SDL_Rect buttonSrc;
	SDL_Rect buttonDst;
	SDL_Surface* buttonSurf;
	SDL_Texture* buttonText;
	bool released;
	enum state { MOUSE_UP, MOUSE_OVER, MOUSE_DOWN };
	int frame;
	int mx, my;
	bool hover;
	int hoverNumber;

public:
	Button(const char* c, SDL_Rect d, Game* gPtr, bool hover);
	~Button();

	bool Clicked() { return frame == 2; }
	void Update(Game* gPtr);
	void Render(Game* gPtr);
	bool GetHover();
	int GetHoverNumber();
};

