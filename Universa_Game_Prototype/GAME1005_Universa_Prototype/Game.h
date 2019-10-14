/**********************************
Filename: Game.h
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 07/02/2019
***********************************/
#pragma once
#include "stdafx.h"
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Spaceship.h"
#include "Explosion.h"
#include "Enemies.h"
#include "Bullet.h"
#include "tinyxml2.h"
#include "StateMachine.h"
#include "Button.h"

#define FPS 60											// Pre-defined FPS for the game
using namespace tinyxml2;

class Game {
public:
	bool leftMouse;
	bool m_bRunning;																						// Is game engine running?
	bool m_bGotTick;																						// Received tick from the timer?
	bool m_bUpPressed;																						// If player pressed up key 
	bool m_bDownPressed;																					// If player pressed down key
	bool m_bLeftPressed;																					// If player pressed left key
	bool m_bRightPressed;																					// If player pressed right key
	bool m_bSpacePressed;																					// If player pressed space bar
	bool m_bMPressed;																						// If player pressed M key
	bool m_bBPressed;																						// If player pressed B key
	bool m_bGPressed;
	int mouseX, mouseY;																						// Mouse X and Y position
	int m_iFPS;																								// Game frame limit
	int m_iTickCtr = 0;																						// Tick counter
	int m_iTickMax = 8;																						// For animation speed
	int m_iScore = 0;																						// Player score counter
	int m_iLives = 3;																						// Player lives counter
	int m_iEnemyHealth;
	vector<int> m_iHighScores = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int check = 9;																							//Used to compare the current score to the next highest saved highscore
	int m_iTotalNumberOfShipsHit = 0;																		// Total kills
	int m_iTimePlayed = 0;																					// Total time played in seconds (even afk hours, for now)
	int m_iNumberOfDeaths = 0;
	const Uint8* m_iKeystates;
	vector<int> m_iSavedScores;																				// Vector to save scores for later reference
	SDL_Window* m_pWindow;		 																			// Game window
	SDL_Renderer* m_pRenderer;																				// Renderer
	SDL_Surface* m_image;																					// Player image surface
	SDL_Surface* m_imageBg;																					// Background image surface
	SDL_Surface* m_imageBg2;
	SDL_Surface* m_imageBg3;
	SDL_Surface* winSurf;
	SDL_Surface* lossSurf;
	SDL_Surface* shieldSurf;
	SDL_Surface* m_boss;																					// Boss surface
	SDL_Surface* m_bosspart;
	SDL_Surface* m_enemyImage;																				// Enemy image surface
	SDL_Surface* m_pEnemyType2;																				// Enemy type 2 image surface
	SDL_Surface* m_imagebullet;																				// Bullet image surface
	SDL_Surface* powerUpTriple;
	SDL_Surface* lazerBlast;
	SDL_Surface* powerUpShield;
	SDL_Surface* powerUpLazer;
	SDL_Surface* m_surfBossHealth;
	SDL_Surface* m_surfHighScoresText;
	SDL_Texture* winText;
	SDL_Texture* lossText;
	SDL_Texture* m_textHighScoresText;
	SDL_Texture* textTriple;
	SDL_Texture* textLazer;
	SDL_Texture* textLazerBlast;
	SDL_Texture* textShield;
	SDL_Texture* shield;
	SDL_Texture* m_texture;																					// Player texture
	SDL_Texture* m_textureBg;																				// Background texture
	SDL_Texture* m_textureBg2;
	SDL_Texture* m_textureBg3;
	SDL_Texture* m_textureEnemy;																			// Enemy texture
	SDL_Texture* m_textureEnemy2;																			// Enemy type 2 texture
	SDL_Texture* m_textureBoss;																				// Boss Texture
	SDL_Texture* m_textureBosspart;
	SDL_Texture* m_textbullet;																				// Bullet texture
	SDL_Texture* m_textBossHealth;
	vector<Bullet*> bullets;																				// Vector list of bullets
	vector<Lazer*> lazers;
	vector<Powerup*> powerup;
	vector<Explosion*> explode;																				// Vector list for explosions
	int m_iEnemyBulletCtr;																					// Enemies bullet counter (To cap maximum enemies' bullets)
	int m_iPowerupCtr;
	bool m_bOneBullet = true;																				// Player bullet firing sequence update. One bullet per key press
	bool m_bThreeBullet = true;																				// Player triple shot firing sequence update. One Spreadshot per key press
	bool m_bLazerBullet = true;																				// Player Lazer shot firing sequence update. Continous fire for 3 seconds
	TTF_Font* font;																							// TTF font 
	TTF_Font* font2;																							// TTF font 
	TTF_Font* font3;																							// TTF font 
	SDL_Surface* message;																					// Message to be made into surface
	SDL_Texture* text;
	SDL_Color textColor;
	SDL_Surface* ttfSurface;																				// The TTF parameters
	SDL_Texture* ttfTexture;																				// The TTF texture
	SDL_Surface* explSurface;
	SDL_Texture* explTexture;
	SDL_Surface* livesSurface;																				// Lives parameters
	SDL_Texture* livesTexture;																				// Lives texture
	SDL_Rect dstrect;
	SDL_Rect dstrectlives;
	SDL_Rect ammoRect;
	SDL_Rect highScoreRect;
	StateMachine* m_pFSM;
	vector<Mix_Music*> m_vMusic;						// Background music (mp3 in our case)
	vector<Mix_Chunk*> m_vSounds;						// Sound effects (wav in our case)
	int m_iVol, m_iLPan, m_iRPan;						// Volume and Panning
	Mix_Chunk* m_pExplSound;

	Game();												// Game constructor
	~Game();											// Game destructor
	void load();										// Load all saved data
	bool init(const char*, int, int, int, int, int);	// Game init
	bool running();										// Game engine running check
	bool tick(vector<Enemies*>&);						// Game engine tick check
	void update(Spaceship&, vector<Enemies*>&);			// Game engine update module
	void handleEvents();								// Game engine event handler
	void render(Spaceship&, vector<Enemies*>&);			// Game engine renderer
	void clean();										// Game engine cleaner										
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	SDL_Rect getTextRect() { return dstrect; }
	SDL_Rect getLivesRect() { return dstrectlives; }
	SDL_Rect getAmmoRect() { return ammoRect; }
	SDL_Rect getHighScoreRect() { return highScoreRect; }
	void setTextRect(SDL_Rect);					// Setter for text rect 
	void setLivesRect(SDL_Rect);					// Setter for lives rect 
	void setAmmoRect(SDL_Rect);
	void setHighScoreRect(SDL_Rect);
	void save();										//Save all data
	StateMachine* GetFSM() { return m_pFSM; }
	bool keyDown(SDL_Scancode c);
	int GetMouseX() { return mouseX; }
	int GetMouseY() { return mouseY; }
	bool GetLeftMouse() { return leftMouse; }
};