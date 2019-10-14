#include "stdafx.h"
#include "Button.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

Button::Button(const char* c, SDL_Rect d, Game* gPtr, bool hover)
{
	buttonSurf = IMG_Load(c);
	buttonText = SDL_CreateTextureFromSurface(gPtr->getRenderer(), buttonSurf);
	SDL_FreeSurface(buttonSurf);
	released = true;
	buttonDst = d;
	buttonSrc.x = buttonSrc.y = 0;
	buttonSrc.w = buttonDst.w;
	buttonSrc.h = buttonDst.h;
	this->hover = hover;
}


Button::~Button()
{
	SDL_DestroyTexture(buttonText);
}

void Button::Update(Game* gPtr)
{
	mx = gPtr->GetMouseX();
	my = gPtr->GetMouseY();
	if (mx < (buttonDst.x + buttonDst.w) && mx > buttonDst.x && my < (buttonDst.y + buttonDst.h) && my > buttonDst.y)
	{
		hoverNumber = 1;
		if (gPtr->GetLeftMouse() && released)
		{
			frame = MOUSE_DOWN;
			released = false;
		}
		else if (!gPtr->GetLeftMouse())
		{
			frame = MOUSE_OVER;
			released = true;
			
		}
		
	}
	else
	{
		frame = MOUSE_UP;
		hoverNumber = 0;
	}
}

void Button::Render(Game* gPtr)
{
	if (!hover)
	{
		buttonSrc.x = buttonDst.w * frame;
	}
	else
	{
		buttonSrc.x = buttonDst.w * hoverNumber;
	}
	SDL_RenderCopy(gPtr->getRenderer(), buttonText, &buttonSrc, &buttonDst);
}

bool Button::GetHover()
{
	return hover;
}

int Button::GetHoverNumber()
{
	return hoverNumber;
}
