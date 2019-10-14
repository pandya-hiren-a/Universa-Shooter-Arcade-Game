/**********************************
Filename: Game.cpp
Author: F-Racing Team
Created On: 24/01/2019
Modified On: 07/02/2019
***********************************/

#include "stdafx.h"
#include <chrono>
#include <iostream>
#include "Game.h"
#include "Bullet.h"
#include "Powerup.h"
#include "Enemies.h"
#include "Scene.h"
using namespace std;
using namespace chrono;

int Bullet::m_iSpeed = 10;																			// Bullet speed
int Powerup::m_iPowerupSpeed = 1.75;
double Bullet::m_dLifespan = 5.0;																	// Bullet's Lifespan
double Powerup::m_dLifespan = 5.0;
int Bullet::m_iScore = 0;
int Bullet::m_iCurrentScore = 0;
int Bullet::m_iLives = 3;

// Game constructor	
Game::Game() {
	this->m_iFPS = FPS;																				// Set current game FPS to default	
	this->m_bGotTick = false;																		// No ticks till now
	this->m_bUpPressed = false;																		// 'W'/'w' not pressed -> default false
	this->m_bDownPressed = false;																	// 'S'/'s' not pressed -> default false
	this->m_bLeftPressed = false;																	// 'A'/'a' not pressed -> default false
	this->m_bRightPressed = false;																	// 'D'/'d' not pressed -> default false
	this->m_bSpacePressed = false;																	// 'Space' not pressed -> default false
	this->m_bMPressed = false;																		// 'M'/'m' not pressed -> default false
	this->m_bBPressed = false;																		// 'B'/'b' not pressed -> default false
	srand(time(NULL));																				// Randomizer. Making sure that random number sequence initiates randomly
}

// Game destructor
Game::~Game() {
	// Nothing needed in the destructor as of now
}

// Load game data
void Game::load()
{
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("scores.xml");
	XMLNode* pRoot = xmlDoc.FirstChild();
	XMLElement* pElement = pRoot->FirstChildElement("NumberOfShipsHit");
	pElement->QueryIntText(&m_iTotalNumberOfShipsHit);
	pElement = pRoot->FirstChildElement("TimePlayed");
	pElement->QueryIntText(&m_iTimePlayed);
	pElement = pRoot->FirstChildElement("NumberOfDeaths");
	pElement->QueryIntText(&m_iNumberOfDeaths);
	pElement = pRoot->FirstChildElement("HighScores");
	XMLElement* pListElement = pElement->FirstChildElement("HighScore");
	for (int i = 0; i < 10; i++)
	{
		pListElement->QueryIntText(&m_iHighScores[i]);
		pListElement = pListElement->NextSiblingElement("HighScore");
	}
	cout << m_iTotalNumberOfShipsHit << " " << m_iTimePlayed << " " << m_iNumberOfDeaths << endl;
}

// Initialize the game engine
bool Game::init(const char* p_pTitle, int p_iXpos, int p_iYpos, int p_iWidth, int p_iHeight, int p_iFlags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {														// Init SDL module and submodules
		cout << "SDL Init Done." << endl;
		m_pWindow = SDL_CreateWindow(p_pTitle, p_iXpos, p_iYpos, p_iWidth, p_iHeight, p_iFlags);	// Create window
		if (m_pWindow != 0) {																		// Check if window creation success or not
			cout << "Window Creation Done." << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);										// Create renderer
			if (m_pRenderer != 0) {																	// Check if renderer creation success or not
				cout << "Renderer Creation Done." << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 250, 250, 250, 255);							// Set default background color for renderer
			}
			else {
				cout << "Renderer Creation Failed." << endl;
				return false;
			}
		}
		else {
			cout << "Window Creation Failed." << endl;
			return false;
		}

		IMG_Init(IMG_INIT_PNG);																		// Initialize image module
		m_image = IMG_Load("playerTiles.png");														// Player image sprite
		m_imageBg = IMG_Load("assets/sky.png");														// Stage Background image
		m_enemyImage = IMG_Load("enemySprite.png");													// Enemies image sprite
		m_pEnemyType2 = IMG_Load("enemy2Sprite.png");												// Enemy type 2 image sprite
		m_imagebullet = IMG_Load("bullet.png");														// Bullet image
		explSurface = IMG_Load("explosion.png");
		m_imageBg2 = IMG_Load("assets/sky.png");
		m_imageBg3 = IMG_Load("assets/sky.png");
		m_boss = IMG_Load("boss.png");
		m_bosspart = IMG_Load("turret.png");
		powerUpLazer = IMG_Load("lazershot.png");
		powerUpShield = IMG_Load("assets/shieldicon.png");
		powerUpTriple = IMG_Load("tripleshot.png");
		shieldSurf = IMG_Load("assets/shield.png");
		lazerBlast = IMG_Load("assets/spirallazer.png");
		m_surfBossHealth = IMG_Load("assets/health.png");
		m_surfHighScoresText = IMG_Load("assets/highscorestext.png");
		winSurf = IMG_Load("assets/winscreen.png");
		lossSurf = IMG_Load("assets/lossscreen.png");

		if (m_image == 0 || m_imageBg == 0 || m_enemyImage == 0 || m_imagebullet == 0 || m_imageBg2 == 0 || m_imageBg3 == 0
			|| m_boss == 0 || m_bosspart == 0){	// If any of the image loading fails, assert
			cout << "Image loading failure. Error Details: " << SDL_GetError() << endl;
			system("pause");
			return false;
		}
		m_textureBg = SDL_CreateTextureFromSurface(m_pRenderer, m_imageBg);							// Create texture for background image
		m_texture = SDL_CreateTextureFromSurface(m_pRenderer, m_image);								// Create texture for player image sprite
		m_textureEnemy = SDL_CreateTextureFromSurface(m_pRenderer, m_enemyImage);					// Create texture for enemy image sprite
		m_textureEnemy2 = SDL_CreateTextureFromSurface(m_pRenderer, m_pEnemyType2);					// Create texture for enemy type 2 image sprite
		m_textbullet = SDL_CreateTextureFromSurface(m_pRenderer, m_imagebullet);					// Create texture for bullet image
		explTexture = SDL_CreateTextureFromSurface(m_pRenderer, explSurface);	
		m_textureBg2 = SDL_CreateTextureFromSurface(m_pRenderer, m_imageBg2);
		m_textureBg3 = SDL_CreateTextureFromSurface(m_pRenderer, m_imageBg3);
		m_textureBoss = SDL_CreateTextureFromSurface(m_pRenderer, m_boss);
		m_textureBosspart = SDL_CreateTextureFromSurface(m_pRenderer, m_bosspart);
		textTriple = SDL_CreateTextureFromSurface(m_pRenderer, powerUpTriple);
		textLazer = SDL_CreateTextureFromSurface(m_pRenderer, powerUpLazer);
		textShield = SDL_CreateTextureFromSurface(m_pRenderer, powerUpShield);
		shield = SDL_CreateTextureFromSurface(m_pRenderer, shieldSurf);
		textLazerBlast = SDL_CreateTextureFromSurface(m_pRenderer, lazerBlast);
		m_textBossHealth = SDL_CreateTextureFromSurface(m_pRenderer, m_surfBossHealth);
		m_textHighScoresText = SDL_CreateTextureFromSurface(m_pRenderer, m_surfHighScoresText);
		winText = SDL_CreateTextureFromSurface(m_pRenderer, winSurf);
		lossText = SDL_CreateTextureFromSurface(m_pRenderer, lossSurf);

		TTF_Init();

		//char buffer[50];

		font = TTF_OpenFont("game_sans_serif_7.ttf", 28);
		font2 = TTF_OpenFont("game_sans_serif_7.ttf", 50);
		font3 = TTF_OpenFont("game_sans_serif_7.ttf", 70);
		textColor = { 255, 255, 255 };

	}
	else {
		cout << "SDL Init Failure." << endl;
		return false;	
	}
	m_pFSM = new StateMachine();
	m_pFSM->changeState(new TitleState(this));
	m_iKeystates = SDL_GetKeyboardState(NULL);

	cout << "INIT Success" << endl;																	// SDL initialization success
	m_bRunning = true;																				// Set game engine to running mode
	load();
	//cout << "Test: " << m_iTotalNumberOfShipsHit << endl;
	if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 8192);
		Mix_AllocateChannels(16);
		// Load the tracks into the Mix_Music vector.
		m_vMusic.reserve(2);
		m_vMusic.push_back(Mix_LoadMUS("./assets/audio/music/NexttoYou.mp3"));
		m_vMusic.push_back(Mix_LoadMUS("./assets/audio/music/Hero_Immortal.mp3"));
		// Load the chunks into the Mix_Chunk vector. 
		m_vSounds.reserve(2);
		m_vSounds.push_back(Mix_LoadWAV("./assets/audio/effects/bullet.wav"));
		m_vSounds.push_back(Mix_LoadWAV("./assets/audio/effects/explosion.wav"));
		m_vSounds.push_back(Mix_LoadWAV("./assets/audio/effects/shield.wav"));

	}
	else {
		cout << "Music Error: " << Mix_GetError();
		return false;
	}
	m_iVol = 128;
	int previousVolume;
	previousVolume = Mix_VolumeChunk(m_vSounds[1], 128);
	Mix_PlayMusic(m_vMusic[0], -1); // Play. -1 = looping.
	
	Mix_VolumeMusic(m_iVol);
	m_iLPan = m_iRPan = 255;

	// Setup the grid
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			Scene::grid.push_back(Scene::gridLocation((j * 63) + 100, (i * 63) + 100, false));
		}
	}

	return true;
}

// Getter for game engine status
bool Game::running() {
	return this->m_bRunning;
}

// game engine update rate regulator
bool Game::tick(vector<Enemies*>& e) {
	auto duration = steady_clock::now().time_since_epoch();
	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / m_iFPS;
	/*
	if (count % (tick * 120) == 0)
	{
	// Needs to make sure only this works and default one from main file is removed
	// Keeping it commented until properly implemented
	// e.push_back(new Enemies());
	}*/

	if (count % tick == 0) {
		if (m_bGotTick == false) {
			m_bGotTick = true;
			return true;
		}
		return false;
	}
	else {
		m_bGotTick = false;
	}
	return false;
}

// Update objects
void Game::update(Spaceship& s, vector<Enemies*>& e) {
	GetFSM()->update(s, e); // Invokes the update of the state machine.
}

// Setter for Text Rect.
void Game::setTextRect(SDL_Rect p_rRect) {
	dstrect.x = p_rRect.x;
	dstrect.y = p_rRect.y;
	dstrect.h = p_rRect.h;
	dstrect.w = p_rRect.w;
}

// Setter for Lives Rect.
void Game::setLivesRect(SDL_Rect p_rLivesRect) {
	dstrectlives.x = p_rLivesRect.x;
	dstrectlives.y = p_rLivesRect.y;
	dstrectlives.h = p_rLivesRect.h;
	dstrectlives.w = p_rLivesRect.w;
}

void Game::setAmmoRect(SDL_Rect ammoRect)
{
	this->ammoRect.x = ammoRect.x;
	this->ammoRect.y = ammoRect.y;
	this->ammoRect.h = ammoRect.h;
	this->ammoRect.w = ammoRect.w;
}

void Game::setHighScoreRect(SDL_Rect highscore)
{
	this->highScoreRect.x = highscore.x;
	this->highScoreRect.y = highscore.y;
	this->highScoreRect.h = highscore.h;
	this->highScoreRect.w = highscore.w;
}

// Game engine events handler
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {																	// Poll for any triggered events
		switch (event.type) {																		// For any event triggered, check the type of the event
		case SDL_QUIT:																				// If SDL quit has been received
			m_bRunning = false;																		// Stop the game engine
			break;
		case SDL_KEYDOWN:																			// If any key has been pressed
			//cout << event.key.keysym.sym << endl;													// Debug: Key code of the key which was pressed
			switch (event.key.keysym.sym) {
			case 'w':																				// If W is pressed, consider it as UP
			case 'W':
				if (!m_bUpPressed)
					m_bUpPressed = true;
				break;

			case 's':																				// If S is pressed, consider it as DOWN
			case 'S':
				if (!m_bDownPressed)
					m_bDownPressed = true;
				break;

			case 'a':																				// If A is pressed, consider it as LEFT
			case 'A':
				if (!m_bLeftPressed)
					m_bLeftPressed = true;
				break;

			case 'd':																				// If D is pressed, consider it as RIGHT
			case 'D':
				if (!m_bRightPressed)
					m_bRightPressed = true;
				break;
			case ' ':																				// If space is pressed, consider it as FIRE
				if (!m_bSpacePressed)
					m_bSpacePressed = true;
				break;
			case 'm':																				// If Z is pressed, consider it as FIRE
			case 'M':
				if (!m_bMPressed)
					m_bMPressed = true;
				break;
			case 'b':
			case 'B':
				if (!m_bBPressed)
					m_bBPressed = true;
				break;
			}
			break;

		case SDL_KEYUP:																				// If pressed key has been released, SDL_KEYUP will be triggered
			switch (event.key.keysym.sym) {
			case 'w':
			case 'W':
				m_bUpPressed = false;
				break;

			case 'a':
			case 'A':
				m_bLeftPressed = false;
				break;

			case 's':
			case 'S':
				m_bDownPressed = false;
				break;

			case 'd':
			case 'D':
				m_bRightPressed = false;
				break;
			case ' ':
				m_bSpacePressed = false;
				m_bOneBullet = true;
				break;
			case 'm':
			case 'M':
				m_bMPressed = false;
				m_bLazerBullet = true;
				break;
			case 'b':
			case 'B':
				m_bBPressed = false;
				m_bThreeBullet = true;
				break;
			case 'g':
			case 'G':
				m_bGPressed =  m_bGPressed == true ? false : true;
				break;

			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftMouse = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftMouse = false;
			}
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			break;
		}
	}
}

// Game engine renderer
void Game::render(Spaceship& s, vector<Enemies*> &e) {
	// Cjange
	GetFSM()->render(this, s, e);

}

//Save game data
void Game::save()
{
	XMLDocument xmlDoc;		 																									//Create the xml Document
	XMLNode* pRoot = xmlDoc.NewElement("Root");																					//Create the root element
	xmlDoc.InsertEndChild(pRoot);  //xmlDoc.InsertFirstChild(pRoot);
	XMLElement* pElement;																										//Create an xmlElement pointer
	pElement = xmlDoc.NewElement("NumberOfShipsHit");																			//Create a new xmlElement for total number of ships hit
	pElement->SetText(m_iTotalNumberOfShipsHit);																				//Save the total number of ships hit
	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("TimePlayed");																					//Create a new xmlElement for time played
	pElement->SetText(m_iTimePlayed + clock() / (int)CLOCKS_PER_SEC);															//Save time played
	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("NumberOfDeaths");																				//Create a new xmlElement for total deaths
	pElement->SetText(m_iNumberOfDeaths); //Save time played
	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("HighScores");
	//m_iHighScores[0] = Bullet::m_iScore;
	for (const auto& highscore : m_iHighScores)//for (int i = 0; i < 10; i++)
	{
		XMLElement* pListElement = xmlDoc.NewElement("HighScore");
		pListElement->SetText(highscore);	//pListElement->SetText(m_iHighScores[i]);
		pElement->InsertEndChild(pListElement);
	}
	pElement->SetAttribute("itemCount", (int)m_iHighScores.size()); //pElement->SetAttribute("itemCount", 10);
	pRoot->InsertEndChild(pElement);
	xmlDoc.SaveFile("scores.xml"); //The file name (f
}

bool Game::keyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

// Cleaning the game engine on exit
void Game::clean() {
	cout << "Cleaning the game." << endl;															// Debug: Traces
	SDL_DestroyTexture(shield);
	SDL_DestroyTexture(m_texture);																	// Destroy the player texture
	SDL_DestroyTexture(m_textureBg);																// Destroy the background texture
	SDL_DestroyTexture(m_textureBg2);
	SDL_DestroyTexture(m_textureEnemy);																// Destroy the enemy texture
	SDL_DestroyTexture(m_textureEnemy2);															// Destroy the enemy type 2 texture
	SDL_DestroyTexture(m_textureBoss);
	SDL_DestroyTexture(m_textbullet);																// Destroy the bullet texture
	SDL_DestroyTexture(ttfTexture);																	// Destroy the text texture
	SDL_DestroyTexture(livesTexture);																// Destroy the text texture
	SDL_DestroyTexture(textLazer);
	SDL_DestroyTexture(textShield);
	SDL_DestroyTexture(textTriple);
	SDL_DestroyTexture(textLazerBlast);
	SDL_DestroyTexture(m_textBossHealth);
	SDL_DestroyTexture(m_textHighScoresText);
	SDL_DestroyTexture(winText);
	SDL_DestroyTexture(lossText);
	SDL_FreeSurface(winSurf);
	SDL_FreeSurface(lossSurf);
	SDL_FreeSurface(m_surfHighScoresText);
	SDL_FreeSurface(m_image);																		// Clear the surface - player image
	SDL_FreeSurface(m_boss);
	SDL_FreeSurface(m_imageBg);																		// Clear the surface - background image 
	SDL_FreeSurface(m_imageBg2);
	SDL_FreeSurface(m_enemyImage);																	// Clear the surface - enemy image 
	SDL_FreeSurface(m_pEnemyType2);																	// Clear the surface - Enemy type 2 image
	SDL_FreeSurface(m_imagebullet);																	// Clear the surface - bullet image
	SDL_FreeSurface(powerUpShield);																	// Clear the surface - lazer image
	SDL_FreeSurface(powerUpLazer);																	// Clear the surface - lazer image
	SDL_FreeSurface(powerUpTriple);																	// Clear the surface - lazer image
	SDL_FreeSurface(shieldSurf);
	SDL_FreeSurface(ttfSurface);																	// Clear the surface - fonts
	SDL_FreeSurface(livesSurface);																	// Clear the surface - lives fonts
	SDL_FreeSurface(lazerBlast);
	SDL_FreeSurface(m_surfBossHealth);
	SDL_DestroyRenderer(m_pRenderer);																// Destroy the renderer
	SDL_DestroyWindow(m_pWindow);																	// Destroy the window
	IMG_Quit();																						// Quit image module
	SDL_Quit();																						// Quit SDL 
	TTF_Quit();

	m_surfHighScoresText = nullptr;
	m_surfBossHealth = nullptr;
	lazerBlast = nullptr;
	shieldSurf = nullptr;
	m_pWindow = nullptr;		 																	// Game window
	m_pRenderer = nullptr;																			// Renderer
	m_image = nullptr;																				// Player image surface
	m_boss = nullptr;
	m_imageBg = nullptr;																			// Background image surface
	m_imageBg2 = nullptr;
	m_imageBg3 = nullptr;
	m_enemyImage = nullptr;																			// Enemy image surface
	m_pEnemyType2 = nullptr; 																		// Enemy type 2 image surface
	m_imagebullet = nullptr;																		// Bullet image surface
	powerUpShield = nullptr;
	powerUpTriple = nullptr;
	powerUpLazer = nullptr;



	m_texture = nullptr;  																			// Player texture
	m_textureBg = nullptr;																			// Background texture
	m_textureBg2 = nullptr;
	m_textureBg3 = nullptr;
	m_textureEnemy = nullptr;																		// Enemy texture
	m_textureEnemy2 = nullptr;																		// Enemy type 2 texture
	m_textureBoss = nullptr;
	m_textbullet = nullptr;																			// Bullet texture

	font = nullptr;
	message = nullptr;
	text = nullptr;
	ttfSurface = nullptr;
	ttfTexture = nullptr;
	livesSurface = nullptr;
	livesTexture = nullptr;

}