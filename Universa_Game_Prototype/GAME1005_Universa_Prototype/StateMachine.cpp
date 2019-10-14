#include "stdafx.h"
#include "StateMachine.h"
#include <chrono>
#include <iostream>
#include "Game.h"
#include "Bullet.h"
#include "Powerup.h"
#include "Scene.h"
#include "Levels.h"
#include "MoveTarget.h"
#include <algorithm>

using namespace std;
using namespace chrono;

//============================================================ STATE ============================================================//

void State::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	//SDL_RenderClear(gamePtr->getRenderer());
	//cout << "Debug: State Render()" << endl;
	SDL_RenderPresent(gamePtr->getRenderer());
}

State::State(Game* gptr)
{
	gamePtr = gptr;
}

State::~State()
{
}

//============================================================ TITLE STATE ============================================================//

void TitleState::update(Spaceship& s, vector<Enemies*>& e)
{
	//cout << "Debug: Title State Update()" << endl;
	if (getHighScoreState() == false)
	{
		for (int i = 0; i < (int)m_vButtons.size(); i++)
		{
			m_vButtons[i]->Update(gamePtr);
		}
		if (gamePtr->keyDown(SDL_SCANCODE_N) == 1)
		{
			gamePtr->GetFSM()->changeState(new GameState(gamePtr));
			return;
		}
		if (m_vButtons[NEWGAME]->Clicked())
		{
			gamePtr->GetFSM()->changeState(new GameState(gamePtr));
		}
		else if (m_vButtons[EXITGAME]->Clicked())
		{
			gamePtr->m_bRunning = false;
		}
		else if (m_vButtons[HIGHSCORES]->Clicked())
		{
			setHighScoreState(true);
		}
		for (int i = 0; i < m_vButtons.size(); i++)
		{
			if (m_vButtons[i]->GetHover())
			{
				if (m_vButtons[CONTROLS]->GetHoverNumber() == 1)
				{
					controls = true;
				}
				else if (m_vButtons[CREDITS]->GetHoverNumber() == 1)
				{
					credits = true;
				}
				else
				{
					controls = false;
					credits = false;
				}
			}
		}
	}
	else if (getHighScoreState() == true)
	{
		m_vButtons[5]->Update(gamePtr);
		if (m_vButtons[5]->Clicked())
		{
			setHighScoreState(false);
			SDL_Delay(200);
		}
		
	}
}

void TitleState::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	if (getHighScoreState())
	{
		SDL_RenderClear(gamePtr->getRenderer());
		SDL_RenderCopy(gamePtr->getRenderer(), m_pText, { 0 }, { 0 });
		SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_textHighScoresText, &highScoresTextSrc, &highScoresTextDst);
		m_vButtons[5]->Render(gamePtr);

		int texW = 0, texH = 0;
		int j = 1;
		char buffer[100];
		
		sprintf_s(buffer, " %d", gamePtr->m_iHighScores[0]);
		m_pSurf = TTF_RenderText_Blended(gamePtr->font3, buffer, gamePtr->textColor);
		highscoreText = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, m_pSurf);
		SDL_FreeSurface(m_pSurf);

		SDL_QueryTexture(highscoreText, NULL, NULL, &texW, &texH);
		gamePtr->setHighScoreRect({ 1024 / 2 - 100, 200, texW, texH });
		temp = SDL_Rect({ 2, 0, texW, texH });
		SDL_RenderCopy(gamePtr->m_pRenderer, highscoreText, &temp, &(gamePtr->getHighScoreRect()));
		SDL_DestroyTexture(highscoreText);
		
		for (int i = 1; i < 6; i++)
		{
			
			if (gamePtr->m_iHighScores[i] != 0) {
				sprintf_s(buffer, " %d", gamePtr->m_iHighScores[i]);
				m_pSurf = TTF_RenderText_Blended(gamePtr->font2, buffer, gamePtr->textColor);
				highscoreText = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, m_pSurf);
				SDL_FreeSurface(m_pSurf);

				SDL_QueryTexture(highscoreText, NULL, NULL, &texW, &texH);
				gamePtr->setHighScoreRect({ 300, 250 + i * 55, texW, texH });
				temp = SDL_Rect({ 2, 0, texW, texH });
				SDL_RenderCopy(gamePtr->m_pRenderer, highscoreText, &temp, &(gamePtr->getHighScoreRect()));
				SDL_DestroyTexture(highscoreText);
			}
		}
		for (int i = 5; i < 10; i++)
		{
			if (gamePtr->m_iHighScores[i] != 0) {
				sprintf_s(buffer, " %d", gamePtr->m_iHighScores[i]);
				m_pSurf = TTF_RenderText_Blended(gamePtr->font2, buffer, gamePtr->textColor);
				highscoreText = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, m_pSurf);
				SDL_FreeSurface(m_pSurf);

				SDL_QueryTexture(highscoreText, NULL, NULL, &texW, &texH);
				gamePtr->setHighScoreRect({ 600, 250 + j * 55, texW, texH });
				temp = SDL_Rect({ 2, 0, texW, texH });
				SDL_RenderCopy(gamePtr->m_pRenderer, highscoreText, &temp, &(gamePtr->getHighScoreRect()));
				SDL_DestroyTexture(highscoreText);
				j++;
			}
		}

		

	}
	if (!getHighScoreState())
	{
		SDL_RenderClear(gamePtr->getRenderer());
		SDL_RenderCopy(gamePtr->getRenderer(), m_pText, { 0 }, { 0 });												// Renders first galaxy background picture
		
		for (int i = 0; i < m_vButtons.size() - 1; i++)
		{
			m_vButtons[i]->Render(gamePtr);
		}
		if (controls == true)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), m_pText, NULL, NULL);
			for (int i = 0; i < m_vButtons.size() - 1; i++)
			{
				if (m_vButtons[i]->GetHoverNumber() == 1)
				{
					m_vButtons[i]->Render(gamePtr);
				}
			}
			SDL_RenderCopy(gamePtr->getRenderer(), m_pText2, &grayBoxSrc, &grayBoxDst);
			for (int i = 0; i < 7; i++)
				SDL_RenderCopy(gamePtr->m_pRenderer, ttfText[i], &ttfRect[i], &ttfDest[i]);
		}
		if (credits == true)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), m_pText, NULL, NULL);
			for (int i = 0; i < m_vButtons.size() - 1; i++)
			{
				if (m_vButtons[i]->GetHoverNumber() == 1)
				{
					m_vButtons[i]->Render(gamePtr);
				}
			}
			SDL_RenderCopy(gamePtr->getRenderer(), m_pText2, &grayBoxSrc, &grayBoxDst);
			for (int i = 0; i < 8; i++)
				SDL_RenderCopy(gamePtr->m_pRenderer, ttfCredits[i], &ttfRect2[i], &ttfDest2[i]);
		}
	}
	
	State::render(gamePtr, s, e);
}

void TitleState::enter()
{
	cout << "Entering Title" << endl;
	m_pSurf = IMG_Load("assets/background.png");
	m_pText = SDL_CreateTextureFromSurface(gamePtr->getRenderer(), m_pSurf);
	SDL_FreeSurface(m_pSurf);

	m_pSurf = IMG_Load("assets/hoverbackground.png");
	m_pText2 = SDL_CreateTextureFromSurface(gamePtr->getRenderer(), m_pSurf);
	SDL_FreeSurface(m_pSurf);

	m_vButtons.push_back(new Button("assets/newgame.png", { 1024 - 577 - 29, 768 - 58 * 3 - 58 - 29, 577, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/highscores.png", { 1024 / 2 - 138, 768 - 58 * 2 - 29 * 2, 577, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/quitgame.png", { 1024 / 2 - 179, 768 - 58 - 29, 577, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/controls.png", { 150, 768 - 58 * 3 - 29, 396 / 2, 29 }, gamePtr, true));
	m_vButtons.push_back(new Button("assets/credits.png", { 110, 768 - 58 * 2, 396 / 2, 29 }, gamePtr, true));
	m_vButtons.push_back(new Button("assets/mainmenu.png", { 1024 / 2 - 180, 768 - 58 * 2, 577, 58 }, gamePtr, false));

	//Mix_PlayMusic(gamePtr->m_vMusic[0], -1); // Play. -1 = looping.

	char buffer[100];
	string controls[] =
	{
		"Destroy the alien ships before they can",
		"                  destroy you!",
		" ",
		"            [W][A][S][D] to move",
		"[Space] to shoot single and triple shot",
		"              [M] to shoot lazer",
		"                  [P] to pause"
	};

	string credits[] =
	{
		"Universa was created by:",
		"Liam Blake                   Maxwell Bojarzin",
		"Kristian Dickson             Cameron Geraats",
		"Christopher Gugelmeier   Roven Hornilla",
		"Nigel Mortley                Hiren Pandya",
		" ",
		"Additional art credit:",
		"Sonya Simpson"
	};

	for (int i = 0; i < 7; i++) {
		sprintf_s(buffer, controls[i].c_str());
		//if(gamePtr->ttfSurface != nullptr)
		SDL_FreeSurface(gamePtr->ttfSurface);
		gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);
		ttfText[i] = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(ttfText[i], NULL, NULL, &texW, &texH);
		gamePtr->setTextRect({ 200, 150 + (i * 30), texW, texH });
		ttfDest[i].x = 1024 / 2 - 824 / 3 - 10;
		ttfDest[i].y = 250 + (i * 30);
		ttfDest[i].w = texW;
		ttfDest[i].h = texH;

		ttfRect[i].x = 0;
		ttfRect[i].y = 0;
		ttfRect[i].h = texH;
		ttfRect[i].w = texW;
		//SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, &ttfRect[i], &(gamePtr->getTextRect()));
		//SDL_RenderPresent(gamePtr->m_pRenderer);
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(buffer, credits[i].c_str());
		//if(gamePtr->ttfSurface != nullptr)
		SDL_FreeSurface(gamePtr->ttfSurface);
		gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);
		ttfCredits[i] = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(ttfCredits[i], NULL, NULL, &texW, &texH);
		gamePtr->setTextRect({ 200, 150 + (i * 30), texW, texH });
		ttfDest2[i].x = 1024 / 2 - 824 / 3 - 30;
		ttfDest2[i].y = 230 + (i * 30);
		ttfDest2[i].w = texW;
		ttfDest2[i].h = texH;

		ttfRect2[i].x = 0;
		ttfRect2[i].y = 0;
		ttfRect2[i].h = texH;
		ttfRect2[i].w = texW;
		//SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, &ttfRect[i], &(gamePtr->getTextRect()));
		//SDL_RenderPresent(gamePtr->m_pRenderer);
	}
	//\r\nPress [N] for a new game.\nPress [P] to pause the game.


}

void TitleState::exit()
{
	cout << "Exiting Title" << endl;
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons.clear();
	}
	SDL_DestroyTexture(m_pText);
}

void TitleState::resume()
{

}

//============================================================ GAME STATE ============================================================//

void GameState::update(Spaceship& s, vector<Enemies*>& e)
{
	runTime++; //add 1 to the runTime each update, to get the number of seconds just divide runTime by 60 because we have 60 frames per second
	if (dst.y >= 768)
	{
		dst.y = dst2.y - 3072;
	}
	if (dst2.y >= 768)
	{
		dst2.y = dst.y - 3072;
	}

	dst.y += 4;
	dst2.y += 4;

	if (initialEnter) {
		s.m_rDst.x = 1024 / 2;
		s.m_rDst.y = 670;
		s.m_x = 1024 / 2;
		s.m_y = 670;
		initialEnter = false;
	}
		
	//========================================================================== CHECKS PLAYERS BOUNDARIES ==========================================================================
	if (gamePtr->m_bUpPressed && s.m_y > 300)																	// If 'W'/'w' is pressed, move player's Y coordinate
		s.MoveY(-1);
	if (gamePtr->m_bDownPressed && s.m_y < 708)																	// If 'S'/'s' is pressed, move player's Y coordinate
		s.MoveY(1);
	if (gamePtr->m_bLeftPressed && s.m_x > 0) {																	// If 'A'/'a' is pressed, move  player's X coordinate. Do not flip the player's image 
		s.MoveX(-1);
		s.m_bRight = false;
	}
	if (gamePtr->m_bRightPressed && s.m_x < 964) {																// If 'D'/'d' is pressed, move player's X coordinate. Flip the player's image 180Deg
		s.MoveX(1);
		s.m_bRight = true;
	}
	s.godMode = gamePtr->m_bGPressed;

	bool ready = true;
	for (int i = 0; i < e.size(); i++)
	{
		e[i]->alienBehaviour->Update();
		if (!e[i]->alienBehaviour->GetReady()) ready = false;
	}
	if (ready)
	{
		Target::flip *= -1;
		for (int i = 0; i < e.size(); i++)
		{
			e[i]->alienBehaviour->GetReady(true);
		}
	}

	//========================================================================== PLAYER'S BULLET CONTROLS (SPACE) (M) (B) ==========================================================================
	if (gamePtr->m_bSpacePressed && gamePtr->m_bOneBullet && !s.powerUpCharges[0]) {													// If ' ' is pressed, fire the bullet
		numberOfShots++;
		Bullet* temp = new Bullet;																				// Create a new bullet pointer
		temp->m_rDst.x = s.m_rDst.x + s.m_rDst.w / 2 - temp->m_rDst.w / 2;										// Bullet's initial position (X coordinate). Player's X coordinate + player sprite's width/2 (brings the bullet location to center of the player's sprite - bullet's width/2 (adjusts the center)
		temp->m_rDst.y = s.m_rDst.y + s.m_rDst.h / 2 - temp->m_rDst.h / 2;										// Bullet's initial position (Y coordinate). Player's Y coordinate + player sprite's height/2 (brings the bullet location to center of the player's sprite - bullet's height/2 (adjusts the center)
		temp->m_Dx = 0;																							// Delta change in X coordinate
		temp->m_Dy = 5;																							// Delta change in Y coordinate
		temp->playerOwned = true;																				// Bullet was fired by the player
		gamePtr->bullets.push_back(temp);																		// Add the bullet into vector list for later processing
		gamePtr->m_bOneBullet = false;																			// Bullet fired. Will be updated when key press is lifted
	}

	if (gamePtr->m_bSpacePressed && gamePtr->m_bThreeBullet && s.powerUpCharges[0] > 0) {						// If ' ' is pressed and TripShot is availible, fire the triple shot bullet
		numberOfShots++;
		Bullet* temp;
		s.powerUpCharges[0]--;
		for (int i = 0; i < 3; i++) {
			temp = new Bullet((i * 2) - 2, 5);																	// Create a new bullet pointer
			//Bullet* temp2 = new Bullet;
			temp->m_rDst.x = s.m_rDst.x + s.m_rDst.w / 2 - temp->m_rDst.w / 2;									// Bullet's initial position (X coordinate). Player's X coordinate + player sprite's width/2 (brings the bullet location to center of the player's sprite - bullet's width/2 (adjusts the center)
			temp->m_rDst.y = s.m_rDst.y + s.m_rDst.h / 2 - temp->m_rDst.h / 2;									// Bullet's initial position (Y coordinate). Player's Y coordinate + player sprite's height/2 (brings the bullet location to center of the player's sprite - bullet's height/2 (adjusts the center)

			temp->playerOwned = true;																			// Bullet was fired by the player
			gamePtr->bullets.push_back(temp);																	// Add the bullet into vector list for later processing
		}
		//Bullet* temp = new Bullet(-2, 5);																		// Create a new bullet pointer
		//Bullet* temp = new Bullet(2, 5);																		// Create a new bullet pointer
		gamePtr->m_bSpacePressed = false;																		// Bullet fired. Will be updated when key press is lifted
	}

	if (gamePtr->m_bMPressed && gamePtr->m_bLazerBullet && s.powerUpCharges[1] > 0) {							// If 'M'/'m' is pressed and Lazer is availible, fire the Lazer
		Lazer* temp;
		s.powerUpCharges[1] = 0;
		
		temp = new Lazer(s);																	// Create a new bullet pointer							
		gamePtr->lazers.push_back(temp);																	// Add the bullet into vector list for later processing
		
		//Bullet* temp = new Bullet(-2, 5);																		// Create a new bullet pointer
		//Bullet* temp = new Bullet(2, 5);																		// Create a new bullet pointer
	}
	
	// Dev testing - Spreadshot 
	/*if (gamePtr->m_bBPressed && gamePtr->m_bThreeBullet) {														// If 'B'/'b' is pressed, fire the hundo shot bullet
		numberOfShots += 50;
		Bullet* temp;// No restriction on press #																// This is just for devs to test stuff
		for (int i = -25; i < 26; i++) {
			temp = new Bullet((i * 0.2), 5);																	// Create a new bullet pointer
																												//Bullet* temp2 = new Bullet;
			temp->m_rDst.x = s.m_rDst.x + s.m_rDst.w / 2 - temp->m_rDst.w / 2;									// Bullet's initial position (X coordinate). Player's X coordinate + player sprite's width/2 (brings the bullet location to center of the player's sprite - bullet's width/2 (adjusts the center)
			temp->m_rDst.y = s.m_rDst.y + s.m_rDst.h / 2 - temp->m_rDst.h / 2;									// Bullet's initial position (Y coordinate). Player's Y coordinate + player sprite's height/2 (brings the bullet location to center of the player's sprite - bullet's height/2 (adjusts the center)

			temp->playerOwned = true;																			// Bullet was fired by the player
			gamePtr->bullets.push_back(temp);																	// Add the bullet into vector list for later processing
		}
		//Bullet* temp = new Bullet(-2, 5);																		// Create a new bullet pointer
		//Bullet* temp = new Bullet(2, 5);																		// Create a new bullet pointer
		gamePtr->m_bThreeBullet = false;
	}*/

	//========================================================================== ENEMIES SHOOTING SPEED (25 TICKS) ==========================================================================
	// Enemy bullet firing sequence - Counter()
	int modEnemyFireSpeed = 100;
	if (e.size() < 6) modEnemyFireSpeed = 100 + (6 - e.size()) * 25;
	if (gamePtr->m_iEnemyBulletCtr >= (30 * modEnemyFireSpeed / 100)) {																		// Enemies bullets firing capping
		gamePtr->m_iEnemyBulletCtr = 0;
		if (e.size() > 0) {
			int counter = e.size();
			int m_iRand = rand() % e.size(); 
			do {																// Select the enemies from the front line only. I.E. enemies no. 8 to MAX
				if (e[m_iRand]->m_bIsAlive && e[m_iRand]->GetCanFire()) 
				{																		// Check if enemy is alive
					Bullet* m_pEnemyBullet = new Bullet;
					m_pEnemyBullet->m_rDst.x = e[m_iRand]->m_rDst.x + e[m_iRand]->m_rDst.w / 2 - m_pEnemyBullet->m_rDst.w / 2;
					m_pEnemyBullet->m_rDst.y = e[m_iRand]->m_rDst.y + e[m_iRand]->m_rDst.h / 2 - m_pEnemyBullet->m_rDst.h / 2;
					if (e[m_iRand]->enemyType != 4)
					{
						m_pEnemyBullet->m_Dx = 0;
						m_pEnemyBullet->m_Dy = 5;
					}
					else
					{
						Vector2 aimPlayer(s.m_rDst.x + s.m_rDst.w/2 - e[m_iRand]->m_rDst.x - e[m_iRand]->m_rDst.w/2,
								s.m_rDst.y + s.m_rDst.h / 2 - e[m_iRand]->m_rDst.y - e[m_iRand]->m_rDst.h / 2 );
						aimPlayer.Normalize();
						float accuracy = 0.7f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.3f - 0.7f)));
						aimPlayer.x *= accuracy;
						aimPlayer.y /= accuracy;
						aimPlayer.Normalize();
						aimPlayer *= 5;
						if (aimPlayer.x > aimPlayer.y) { float temp = aimPlayer.x; aimPlayer.x = aimPlayer.y; aimPlayer.y = temp; }
						m_pEnemyBullet->m_Dx = aimPlayer.x;
						m_pEnemyBullet->m_Dy = aimPlayer.y;
					}
					gamePtr->bullets.push_back(m_pEnemyBullet);
					m_pEnemyBullet->playerOwned = false;		// Bullet is fired by enemy
					m_iRand = -1;
				}
				else
				{
					m_iRand++;
					if (m_iRand >= e.size()) m_iRand = 0;
					counter--;
				}
			} while (m_iRand != -1 && counter > 0);
		}
	}
	//========================================================================== POWERUP DROP SPEED (300 TICKS) ==========================================================================
	if (gamePtr->m_iPowerupCtr == 300) {																		// Enemies bullets firing capping
		gamePtr->m_iPowerupCtr = 0;
		if (e.size() > 0) {
			int m_iRand = rand() % e.size();																	// Select the enemies from the front line only. I.E. enemies no. 8 to MAX
			if (e[m_iRand]->m_bIsAlive) {																		// Check if enemy is alive
				Powerup* tripleshot = new Powerup;
				tripleshot->m_rDst.x = e[m_iRand]->m_rDst.x + e[m_iRand]->m_rDst.w / 2 - tripleshot->m_rDst.w / 2;
				tripleshot->m_rDst.y = e[m_iRand]->m_rDst.y + e[m_iRand]->m_rDst.h / 2 - tripleshot->m_rDst.h / 2;
				tripleshot->m_Dx = 1;
				tripleshot->m_Dy = 3;
				gamePtr->powerup.push_back(tripleshot);
				tripleshot->playerOwned = false;																// powerup is dropped by enemy
			}
		}
	}
	else {
		gamePtr->m_iEnemyBulletCtr++;
		gamePtr->m_iPowerupCtr++;
	}

	// If any of the button pressed, advance the sprite animation.
	if (gamePtr->m_bUpPressed || gamePtr->m_bDownPressed || gamePtr->m_bLeftPressed || gamePtr->m_bRightPressed || gamePtr->m_bSpacePressed || gamePtr->m_bMPressed) {
		if (gamePtr->m_iTickCtr == gamePtr->m_iTickMax) {
			gamePtr->m_iTickCtr = 0;
			s.AdvanceAnim();
		}
		gamePtr->m_iTickCtr++;
	}
	// Else start the idle animation
	else {
		gamePtr->m_iTickCtr = 0;
		s.SetIdle();
	}

	// Set all the enemies in idle state
	for (int i = 0; i < e.size(); i++) {
		e[i]->SetIdle();
	}

	int i = 0;
	while (i < (int)gamePtr->bullets.size())																	// While there are bullets present in the vector list
	{
		gamePtr->bullets[i]->Update(gamePtr->m_pRenderer, s, (vector<Enemies*>&)e, (vector<Explosion*>&)gamePtr->explode, 14, gamePtr->m_iScore, gamePtr->m_iTotalNumberOfShipsHit, kills);			// Update the bullet's location
		if (gamePtr->bullets[i]->m_bKillMeNow)																	// If bullet is past its lifespan
		{
			delete gamePtr->bullets[i];																			// Clear the bullet's allocated space, 
			gamePtr->bullets.erase(gamePtr->bullets.begin() + i);												// remove it from the vector list
			gamePtr->bullets.shrink_to_fit();
		}
		else i++;																								// Advance further
	}
	// Similar to bullets updates, we need to update explosion frames as well
	int k = 0;
	while (k < (int)gamePtr->lazers.size())
	{
		gamePtr->lazers[k]->Update(s, e, gamePtr->m_iScore, gamePtr->m_iTotalNumberOfShipsHit, kills, (vector<Explosion*>&)gamePtr->explode);
		if (gamePtr->lazers[k]->m_bKillMeNow)
		{
			delete gamePtr->lazers[k];
			gamePtr->lazers.erase(gamePtr->lazers.begin() + k);
			gamePtr->lazers.shrink_to_fit();
		}
		else k++;
	}

// Power up update 
	i = 0;
	while (i < (int)gamePtr->powerup.size())																	// While there are bullets present in the vector list
	{
		gamePtr->powerup[i]->Update(gamePtr->m_pRenderer, s, (vector<Enemies*>&)e);								// Update the bullet's location
		if (gamePtr->powerup[i]->m_bKillMeNow)																	// If bullet is past its lifespan
		{
			delete gamePtr->powerup[i];																			// Clear the bullet's allocated space, 
			gamePtr->powerup.erase(gamePtr->powerup.begin() + i);												// remove it from the vector list
			gamePtr->powerup.shrink_to_fit();
		}
		else i++;																								// Advance further
	}


	int j = 0;
	//cout << "FSM Update - Explode Size: " << gamePtr->explode.size() << endl;
	while (j < (int)gamePtr->explode.size()) {																	// While there are explosions objects present in the vector list
		if (gamePtr->explode[j]->m_bFinished) {																	// If the explosion has been marked as completed,
			//cout << "Explosion Done." << endl;
			delete gamePtr->explode[j];																			// Delete that explosion object
			gamePtr->explode[j] = nullptr;
			gamePtr->explode.erase(gamePtr->explode.begin() + j);
			gamePtr->explode.shrink_to_fit();
		}
		else {																									// If the explosion hasn't been marked for deletion yet,
			gamePtr->explode[j]->update();																		// Update the sprite of the explosion
		}
		j++;
	}
	if (gamePtr->keyDown(SDL_SCANCODE_P) == 1)
	{
		gamePtr->GetFSM()->pushState(new PauseState(gamePtr));
		return;
	}
	// Dev Shield - Removed
	if (gamePtr->keyDown(SDL_SCANCODE_T) == 1)
	{
		//if (s.powerUpCharges[3] == 0)
		//{
		//	s.powerUpCharges[3] += 1;
		//}
	}
	if (gamePtr->keyDown(SDL_SCANCODE_L) == 1)
	{
		//if (s.powerUpCharges[1] == 0)
		//{
		//	s.powerUpCharges[1] += 1;
		//}
	}

	if (Bullet::m_iLives <= 0) {
		gamePtr->m_iNumberOfDeaths++;
		gamePtr->GetFSM()->changeState(new LossState(gamePtr));
		return;
	}

	//========================================================================== WHERE LEVELS ARE CREATED =========================================================================================
	// Dynamic generation of enemies on every 15 seconds
	Level1* lvl1_T = dynamic_cast<Level1*>(currentScene);
	if (lvl1_T != nullptr) {
		lvl1_T->Update();
	}

	if (Bullet::m_iLives >= 1 && e.size() == 0)
	{
		string levelComplete;
		Level1* lvl1Temp = dynamic_cast<Level1*>(currentScene);
		Level2* lvl2Temp = dynamic_cast<Level2*>(currentScene);
		Level3* lvl3Temp = dynamic_cast<Level3*>(currentScene);
		Level4* lvl4Temp = dynamic_cast<Level4*>(currentScene);
		Level5* lvl5Temp = dynamic_cast<Level5*>(currentScene);
		if (lvl1Temp != nullptr)
		{
			s.m_x = 1024 / 2;
			s.m_y = 670;
			s.m_rDst.x = 1024 / 2;
			s.m_rDst.y = 670;
			SetScene(new Level2(gamePtr));
			// Reset Grid
			int w = 0;
			while (w < Scene::grid.size()) {
				Scene::grid[w++].isLocked = false;
			}
			
			levelComplete = "Level 2";
		}
		else if (lvl2Temp != nullptr)
		{
			s.m_x = 1024 / 2;
			s.m_y = 670;
			s.m_rDst.x = 1024 / 2;
			s.m_rDst.y = 670;
			SetScene(new Level3(gamePtr));
			// Reset Grid
			int w = 0;
			while (w < Scene::grid.size()) {
				Scene::grid[w++].isLocked = false;
			}

			levelComplete = "Level 3";
		}
		else if (lvl3Temp != nullptr)
		{
			s.m_x = 1024 / 2;
			s.m_y = 670;
			s.m_rDst.x = 1024 / 2;
			s.m_rDst.y = 670;
			SetScene(new Level4(gamePtr));
			// Reset Grid
			int w = 0;
			while (w < Scene::grid.size()) {
				Scene::grid[w++].isLocked = false;
			}
			levelComplete = "Level 4";
		}
		else if (lvl4Temp != nullptr)
		{
			s.m_x = 1024 / 2;
			s.m_y = 670;
			s.m_rDst.x = 1024 / 2;
			s.m_rDst.y = 670;
			SetScene(new Level5(gamePtr));
			level5 = true;
			// Reset Grid
			int w = 0;
			while (w < Scene::grid.size()) {
				Scene::grid[w++].isLocked = false;
			}
			levelComplete = "Level 5";
		}
		else 
		{
			int w = 0;
			while (w < Scene::grid.size()) {
				Scene::grid[w++].isLocked = false;
			}
			gamePtr->GetFSM()->changeState(new WinState(gamePtr));
			// Reset Grid
			
			return;
			//levelComplete = "Error";
		}

		
		//========================================================================== WHERE "LEVEL X" IS CREATED ==========================================================================
		SDL_SetRenderDrawColor(gamePtr->getRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(gamePtr->getRenderer());
		char buffer[100];
		sprintf_s(buffer, levelComplete.c_str());
		SDL_FreeSurface(gamePtr->ttfSurface);
		gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font2, buffer, gamePtr->textColor);
		gamePtr->ttfTexture = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(gamePtr->ttfTexture, NULL, NULL, &texW, &texH);
		gamePtr->setTextRect({ 512 - texW / 2, 364 - texH / 2, texW, texH });
		SDL_Rect srcRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = texH;
		srcRect.w = texW;

		SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, &srcRect, &gamePtr->getTextRect());
		SDL_RenderPresent(gamePtr->getRenderer());
		SDL_Delay(2000);
		//gamePtr->GetFSM()->changeState(new Level2State(gamePtr));

		//if(lvl3Temp != nullptr)
			//SetScene(new Level2(gamePtr));

		//return;
	}

	//cout << "Bullet Size: " << gamePtr->bullets.capacity() << endl;
	//cout << "Enemies Size: " << e.capacity() << endl;
	//cout << "Expl. Size: " << gamePtr->explode.capacity() << endl;
}

void GameState::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	/*cout << "Rendering Game..." << endl;
	SDL_SetRenderDrawColor(gamePtr->getRenderer(), 0, 255, 0, 255);
	State::render();*/

	

	// Clear the current render first
	SDL_RenderClear(gamePtr->m_pRenderer);
	// Render Background
	SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureBg, &src, &dst, 0, 0, SDL_FLIP_NONE);
	SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureBg2, &src, &dst2, 0, 0, SDL_FLIP_NONE);
	
	//========================================================================== RENDER ENEMIES HERE ==========================================================================
	for (int i = 0; i < e.size(); i++) {
		if (e[i]->enemyType == 1) {
			// assign enemy type 1 and render the image of type 1.
			// Type assignment necessary to perform proper animation of the sprites
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureEnemy, e[i]->GetSrc(), e[i]->GetDst(), e[i]->transform->angle, 0, SDL_FLIP_VERTICAL);
		}
		else if (e[i]->enemyType == 2){
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureEnemy2, e[i]->GetSrc(), e[i]->GetDst(), e[i]->transform->angle, 0, SDL_FLIP_VERTICAL);
			e[i]->enemyType = 2;
		}
		else if (e[i]->enemyType == 3){
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureBoss, e[i]->GetSrc(), e[i]->GetDst(), 0, 0, SDL_FLIP_VERTICAL);
			e[i]->enemyType = 3;
		}
		else {
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textureBosspart, e[i]->GetSrc(), e[i]->GetDst(), 0, 0, SDL_FLIP_VERTICAL);
			e[i]->enemyType = 4;
		}
		//SDL_RenderDrawRect(gamePtr->m_pRenderer, e[i]->GetDst());						// Draws white rectangle around object
	}

	//========================================================================== PLAYER INVINCIBLE/SHIELD POWERUP ==========================================================================
	// Render Player character
	// Check if timer activated or not. 
	if (Timer::m_bTimerNeeded) {														
		//cout << "Timer: " << Timer::GetDeltaTime() << endl;
		// Get the tick from the timer, if it's 0.5 or greater, flip the visibility
		if (Timer::GetDeltaTime() > 0.3f) {
			m_bPlayerVisible = !m_bPlayerVisible;
			// If current blink reached max blink, reset
			if (Timer::m_iCurrentBlink >= Timer::m_iBlinks) {
				// Reset timer
				Timer::ResetTimer();
				// Timer not needed anymore
				Timer::m_bTimerNeeded = false;
				// Enable player visibility 
				m_bPlayerVisible = true;
			}
			// If elapsed time isn't more than 0.5s
			else {
				// Increase blinks
				Timer::m_iCurrentBlink++;
				// Reset start timer
				Timer::m_iStartTick = SDL_GetTicks();
			}
		}
	}
	
	// If player visibility is set, render the player
	if (m_bPlayerVisible)
	{
		if (s.godMode)
			SDL_SetTextureColorMod(gamePtr->m_texture, (Uint8)50, 250, 50);
		else
			SDL_SetTextureColorMod(gamePtr->m_texture, 255, 255, 255);
		SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_texture, s.GetSrc(), s.GetDst(), 0, 0, (s.m_bRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
	}
	
	// Render Shield if Active
	if (s.powerUpCharges[3])
	{
		SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->shield, &shieldSrc, s.GetDst());
	}

	// Render Bullets
	for (int i = 0; i < (int)gamePtr->bullets.size(); i++) {
		// If it's the player bullet, no need to flip the image of bullet
		float angle = atan2(gamePtr->bullets[i]->m_Dy, gamePtr->bullets[i]->m_Dx) * 180.0f / M_PI - 90.0f;
		if (gamePtr->bullets[i]->playerOwned)
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textbullet, gamePtr->bullets[i]->GetSrc(), gamePtr->bullets[i]->GetDst(), 0, 0, SDL_FLIP_NONE);
		else
			SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->m_textbullet, gamePtr->bullets[i]->GetSrc(), gamePtr->bullets[i]->GetDst(), angle, 0, SDL_FLIP_VERTICAL);
	}

	for (int i = 0; i < (int)gamePtr->lazers.size(); i++)
	{
		SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->textLazerBlast, gamePtr->lazers[i]->GetSrc(), gamePtr->lazers[i]->GetDst());
	}

	//========================================================================== WHERE POWERUPS ARE RENDERED ==========================================================================
	for (int i = 0; i < gamePtr->powerup.size(); i++)
	{
		if (gamePtr->powerup[i]->poweruptype == 0)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->textTriple, gamePtr->powerup[i]->GetSrc(), gamePtr->powerup[i]->GetDst());
		}
		if (gamePtr->powerup[i]->poweruptype == 1)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->textLazer, gamePtr->powerup[i]->GetSrc(), gamePtr->powerup[i]->GetDst());
		}
		if (gamePtr->powerup[i]->poweruptype == 3)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->textShield, gamePtr->powerup[i]->GetSrc(), gamePtr->powerup[i]->GetDst());
		}
	}

	// As per the size of the explode vector, render the explosion for each object present in the vector
	for (int i = 0; i < (int)gamePtr->explode.size(); i++) {
		SDL_RenderCopyEx(gamePtr->m_pRenderer, gamePtr->explTexture, &gamePtr->explode[i]->m_rSrc, &gamePtr->explode[i]->m_rDst, 0, 0, SDL_FLIP_NONE);
	}


	//========================================================================== WHERE SCORE/LIVES/AMMO/POWERUPS HUD IS ==========================================================================
	char buffer[50];
	char buffer2[50];
	SDL_Texture* ttfTextlocal;
	SDL_Surface* ttfSurflocal;

	//gamePtr->font = TTF_OpenFont("arial.ttf", 28);
	//gamePtr->textColor = { 255, 0, 0 };

	sprintf_s(buffer, "Score: %d", Bullet::m_iScore);

	ttfSurflocal = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);							// TTF Texture for displaying score board
	ttfTextlocal = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, ttfSurflocal);
	SDL_FreeSurface(ttfSurflocal);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(ttfTextlocal, NULL, NULL, &texW, &texH);
	gamePtr->setTextRect({ 15, 720, texW, texH });																// Sets score to bottom left
	SDL_Rect* temp = new SDL_Rect({ 0, 0, 365, 40 });
	SDL_RenderCopy(gamePtr->m_pRenderer, ttfTextlocal, temp, &(gamePtr->getTextRect()));

	SDL_DestroyTexture(ttfTextlocal);

	
	SDL_Surface* livesSurflocal;

	livesSurflocal = TTF_RenderText_Blended(gamePtr->font, buffer2, gamePtr->textColor);
	
	SDL_FreeSurface(livesSurflocal);
	delete temp;

	SDL_Texture* ammoCounterlocal;
	sprintf_s(buffer, ": %d", s.powerUpCharges[0]);
	livesSurflocal = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);
	ammoCounterlocal = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, livesSurflocal);
	SDL_FreeSurface(livesSurflocal);


	SDL_QueryTexture(ammoCounterlocal, NULL, NULL, &texW, &texH);
	gamePtr->setAmmoRect({ 911, 664, texW, texH });
	temp = new SDL_Rect({ 2, 0, 365, 40 });
	SDL_RenderCopy(gamePtr->m_pRenderer, ammoCounterlocal, temp, &(gamePtr->getAmmoRect()));
	delete temp;
	SDL_DestroyTexture(ammoCounterlocal);

		if (Bullet::m_iLives == 3)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife1);
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife2);
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife3);
		}
		else if (Bullet::m_iLives == 2)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife1);
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife2);
		}
		else if (Bullet::m_iLives == 1)
		{
			SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_texture, &srcLife, &dstLife1);
		}
			
		//if (level5 == true)
		//{
		//	SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->m_textBossHealth, &bossSrc, &bossDst);
		//	if (Boss::enemyHealth >= 41)
		//	{
		//		if (Boss::enemyHealth--)
		//		{
		//		bossSrc.x += 943;
		//		}
		//	}
		//	if (Boss::enemyHealth >= 31 && Boss::enemyHealth <= 40)
		//	{
		//		bossSrc.y += 80;
		//		if (Boss::enemyHealth--)
		//		{
		//			bossSrc.x += 943;
		//		}
		//	}
		//}
	SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->textTriple, &srcTriple, &dstTriple);

	SDL_RenderPresent(gamePtr->m_pRenderer);
}

//========================================================================== GAMESTATE ENTER ==========================================================================
void GameState::enter()
{
	if (currentScene != nullptr)
	{
		currentScene->Cleanup();
	}	
	initialEnter = true;
	level5 = false;
	Bullet::m_iLives = 3;
	runTime = 0;
	numberOfShots = 0;
	kills = 0;

	Timer::m_bTimerNeeded = false;
	if (gamePtr->GetFSM()->getEnemies()->size() > 0)
	{
		//for (int i = 0; i < gamePtr->GetFSM()->getEnemies()->size(); i++)
		//{
		gamePtr->GetFSM()->getEnemies()->clear();
		//}
	}

	// Open up the grid when beginning the game state
	//for (Scene::gridLocation obj : Scene::grid) {
	//	obj.isLocked = false;
	//}
	for (int i = 0; i < Scene::grid.size(); i++)
	{
		Scene::grid[i].isLocked = false;
	}
	// Prepare the waypoints for the enemies

	PathFollowing::prepareWaypoints();

	SetScene(new Level1(gamePtr));																			// Set what scene to start the game on

	gamePtr->m_iVol = 80;
	Mix_VolumeMusic(gamePtr->m_iVol);
	Mix_PlayMusic(gamePtr->m_vMusic[1], -1);																// Play. -1 = looping.

	// Print out first level screen
	{
		string levelComplete = "Level 1";
		SDL_SetRenderDrawColor(gamePtr->getRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(gamePtr->getRenderer());
		char buffer[100];
		sprintf_s(buffer, levelComplete.c_str());
		SDL_FreeSurface(gamePtr->ttfSurface);
		gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font2, buffer, gamePtr->textColor);
		gamePtr->ttfTexture = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(gamePtr->ttfTexture, NULL, NULL, &texW, &texH);
		gamePtr->setTextRect({ 512 - texW / 2, 364 - texH / 2, texW, texH });
		SDL_Rect srcRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = texH;
		srcRect.w = texW;

		SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, &srcRect, &gamePtr->getTextRect());
		SDL_RenderPresent(gamePtr->getRenderer());
		SDL_Delay(2000);
	}
}

void GameState::exit()
{
	cout << Bullet::m_iScore << endl;
	cout << numberOfShots << endl;
	cout << kills << endl;
	cout << (kills / numberOfShots) << endl;
	Bullet::m_iScore += ((kills / numberOfShots) * 200);
	Bullet::m_iCurrentScore += ((kills / numberOfShots) * 200);
	cout << Bullet::m_iScore << endl;
	cout << runTime << endl;
	Bullet::m_iScore -= ((runTime / 60) / 3);
	Bullet::m_iCurrentScore -= ((runTime / 60) / 3);

	cout << Bullet::m_iScore << endl;
	gamePtr->m_iHighScores.push_back(Bullet::m_iScore);														//Add players score to all the highscores
	sort(gamePtr->m_iHighScores.begin(), gamePtr->m_iHighScores.end());										//Sort the highscores to see where the current one fits in the top 10
	reverse(gamePtr->m_iHighScores.begin(), gamePtr->m_iHighScores.end());									//reverse the order of the sort to make the highest score on the top
	gamePtr->m_iHighScores.pop_back();																		//removes the lowest score to maintain only top 10 (could be players current score)
	gamePtr->save();
	Bullet::m_iScore = 0;

	Mix_PlayMusic(gamePtr->m_vMusic[0], -1); // Play. -1 = looping.
	//SDL_FreeSurface(gamePtr->ttfSurface);
	//SDL_DestroyTexture(gamePtr->ttfTexture);
	currentScene->Cleanup();
	currentScene = nullptr;
}

void GameState::resume()
{
}

void GameState::SetScene(Scene* _scene)
{
	if (currentScene != NULL)
	{
		currentScene->Cleanup();
		delete currentScene;
	}
	currentScene = _scene;
	//currentScene->game = this;
	currentScene->Setup();
}

//============================================================ PAUSE STATE ============================================================//

void PauseState::update(Spaceship& s, vector<Enemies*>& e)
{

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Update(gamePtr);
	}
	if (m_vButtons[MAINMENU]->Clicked())
	{
		SDL_Delay(200);
		gamePtr->GetFSM()->changeState(new TitleState(gamePtr));
		return;
	}
	else if (m_vButtons[RESUME]->Clicked())
	{
		gamePtr->GetFSM()->popState();
	}
}

void PauseState::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	//cout << "Debug: Rendering Pause..." << endl;
	//SDL_SetRenderDrawColor(gamePtr->getRenderer(), 255, 255, 0, 40);
	//State::render(gamePtr, s, e);

	for (int i = 0; i < m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render(gamePtr);
	}
	State::render(gamePtr, s, e);
}

void PauseState::enter()
{
	//cout << "Debug: Pausing Game" << endl;
	m_vButtons.push_back(new Button("assets/resume.png", { 1024 / 2 - 180, 768 / 2 - 58, 396, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/mainmenu2.png", { 1024 / 2 - 180, 768 / 2 + 29, 396, 58 }, gamePtr, false));
}

void PauseState::exit()
{
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons.clear();
	}
}

void PauseState::resume()
{

}

//============================================================ WIN GAME STATE ============================================================//

void WinState::update(Spaceship& s, vector<Enemies*>& e)
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Update(gamePtr);
	}
	if (m_vButtons[MAINMENU]->Clicked())
	{
		SDL_Delay(200);
		gamePtr->GetFSM()->changeState(new TitleState(gamePtr));
		return;
	}
	else if (m_vButtons[PLAYAGAIN]->Clicked())
	{
		gamePtr->GetFSM()->changeState(new GameState(gamePtr));
	}
}

void WinState::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	SDL_RenderClear(gamePtr->getRenderer());
	SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->winText, NULL, NULL);
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render(gamePtr);
	}
	char buffer[100];
	int texW = 0, texH = 0;
	sprintf_s(buffer, " %d", Bullet::m_iCurrentScore);
	m_pSurf = TTF_RenderText_Blended(gamePtr->font3, buffer, gamePtr->textColor);
	highscoreText = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, m_pSurf);
	SDL_FreeSurface(m_pSurf);

	SDL_QueryTexture(highscoreText, NULL, NULL, &texW, &texH);
	gamePtr->setHighScoreRect({ 1024 / 2 + 12, 384, texW, texH });
	temp = SDL_Rect({ 2, 0, texW, texH });
	SDL_RenderCopy(gamePtr->m_pRenderer, highscoreText, &temp, &(gamePtr->getHighScoreRect()));
	SDL_DestroyTexture(highscoreText);
	State::render(gamePtr, s, e);
}

void WinState::enter()
{
	//cout << "Debug: Win Game" << endl;

	/*char buffer[80];
	sprintf_s(buffer, "Congratulations, you beat the game! (C) - Continue  (ESC) - Title Screen");

	gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);
	gamePtr->ttfTexture = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);
	SDL_FreeSurface(gamePtr->ttfSurface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(gamePtr->ttfTexture, NULL, NULL, &texW, &texH);
	gamePtr->setTextRect({ 50, 760 / 2, texW, texH });

	SDL_Rect* temp = new SDL_Rect({ 0, 0, texW, texH });
	SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, temp, &(gamePtr->getTextRect()));
	SDL_RenderPresent(gamePtr->m_pRenderer);
	delete temp;*/

	m_vButtons.push_back(new Button("assets/playagain.png", { 1024 / 2 - 180, 768 / 2 + 250 - 29 * 2, 396, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/mainmenu2.png", { 1024 / 2 - 180, 768 / 2 + 29 + 250, 396, 58 }, gamePtr, false));
}

void WinState::exit()
{
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons.clear();
	}
}

void WinState::resume()
{
}

void WinState::SetScene(Scene* _scene)
{
	if (currentScene != NULL)
	{
		currentScene->Cleanup();
		delete currentScene;
	}
	currentScene = _scene;
	//currentScene->game = this;
	currentScene->Setup();
}

//============================================================ LOSE GAME STATE ============================================================//

void LossState::update(Spaceship& s, vector<Enemies*>& e)
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Update(gamePtr);
	}
	if (m_vButtons[MAINMENU]->Clicked())
	{
		SDL_Delay(200);
		gamePtr->GetFSM()->changeState(new TitleState(gamePtr));
		return;
	}
	else if (m_vButtons[PLAYAGAIN]->Clicked())
	{
		gamePtr->GetFSM()->changeState(new GameState(gamePtr));
	}
}

void LossState::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{
	SDL_RenderClear(gamePtr->getRenderer());
	SDL_RenderCopy(gamePtr->getRenderer(), gamePtr->lossText, NULL, NULL);

	for (int i = 0; i < m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render(gamePtr);
	}
	State::render(gamePtr, s, e);
}

void LossState::enter()
{
	//cout << "Debug: Loss Game" << endl;

	/*char buffer[80];
	sprintf_s(buffer, "You died. Play again? (Y) - Yes (ESC) - Title Screen");

	gamePtr->ttfSurface = TTF_RenderText_Blended(gamePtr->font, buffer, gamePtr->textColor);
	gamePtr->ttfTexture = SDL_CreateTextureFromSurface(gamePtr->m_pRenderer, gamePtr->ttfSurface);
	SDL_FreeSurface(gamePtr->ttfSurface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(gamePtr->ttfTexture, NULL, NULL, &texW, &texH);
	gamePtr->setTextRect({ 200, 760 / 2, texW, texH });

	SDL_Rect* temp = new SDL_Rect({ 0, 0, texW, texH });
	SDL_RenderCopy(gamePtr->m_pRenderer, gamePtr->ttfTexture, temp, &(gamePtr->getTextRect()));
	SDL_RenderPresent(gamePtr->m_pRenderer);
	delete temp;*/

	m_vButtons.push_back(new Button("assets/playagain.png", { 1024 / 2 - 180, 768 / 2 + 250 - 29*2, 396, 58 }, gamePtr, false));
	m_vButtons.push_back(new Button("assets/mainmenu2.png", { 1024 / 2 - 180, 768 / 2 + 29 + 250, 396, 58 }, gamePtr, false));
}

void LossState::exit()
{
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons.clear();
	}
}

void LossState::resume()
{
}

//============================================================ STATE MACHINE ============================================================//

void StateMachine::update(Spaceship& s, vector<Enemies*>& e)
{
	enemies = &e;

	if (!m_vStates.empty())
		m_vStates.back()->update(s, e);
}

void StateMachine::render(Game* gamePtr, Spaceship& s, vector<Enemies*> &e)
{

	if (!m_vStates.empty())
		m_vStates.back()->render(gamePtr, s, e);
}

void StateMachine::pushState(State* state)
{
	m_vStates.push_back(state);
	m_vStates.back()->enter();
}

void StateMachine::changeState(State* state)
{
	cout << "Changing State... " << endl;
	while (!m_vStates.empty())
	{
		m_vStates.back()->exit();
		delete m_vStates.back(); // De-allocating the state in the heap.
		m_vStates.back() = nullptr; // Nullifying pointer to the de-allocated state.
		m_vStates.pop_back(); // Removes the now-null pointer from the vector.
	}
	m_vStates.push_back(state);
	state->enter();
}

void StateMachine::popState()
{
	cout << "Pop State " << endl;
	if (!m_vStates.empty())
	{
		m_vStates.back()->exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->resume();
}

void StateMachine::popState(int i)
{
	cout << "Pop State " << endl;
	if (!m_vStates.empty())
	{
		m_vStates.front()->exit();
		delete m_vStates.front();
		m_vStates.front() = nullptr;
		m_vStates.pop_back();
	}
//	m_vStates.back()->resume();
}

void StateMachine::clean()
{
	cout << "Clearning States" << endl;
	while (!m_vStates.empty()) // Because we can exit the game in the pause state with the window's 'X'.
	{						   // Ensures that ALL states left in the vector are cleaned up.
		m_vStates.back()->exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}
