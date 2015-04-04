#include "Game.h"
#include "Vector2D.h"
#include <fstream>
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "MiscDataDef.h"
#include "Animation.h"
#include "Event.h"
#include "GraphicsSystem.h"
#include "LevelManager.h"
#include "UnitManager.h"
#include "Level.h"
#include "Color.h"
#include "SoundHandler.h"
#include <SDL.h>
#include <time.h>

Game::Game(void)
	:mpColor(255,0,0,255)
{
	mpGraphicsSystem = nullptr;
	mpInputManager = nullptr;
	mpResourceManager = nullptr;
	mpLevelManager = nullptr;
	mpFont = nullptr;
	mHUDLoc = Vector2D(0.0f, 0.0f);
	mScoreLoc = Vector2D(0.0f, 0.0f);
	mBonusLoc = Vector2D(0.0f, 0.0f);
	mLevelNameLoc = Vector2D(0.0f, 0.0f);
	mOriginPoint = Vector2D(0.0f, 0.0f);

	mStart = true;
	mStartOptions = false;
	mWin = false;
	mLose = false;
	mGameOptions =  false;

	mScore = 0;
	mBonus = 0;
	mLevelNameString = "";
	mNeedClean = false;
	mKeepLooping = true;

	mpSoundHandler = nullptr;
}

Game::~Game(void)
{
	cleanup();
}

bool Game::init(int width, int height)
{
	mDifficultyLevel = 1;
	mScore = 0;
	mLives = 2;

	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "This could be a problem, " << SDL_GetError() << std::endl;
		return false;
	}

	mpSoundHandler = New SoundHandler();

	mpInputManager = New InputManager();
	mpInputManager->init();

	mpGraphicsSystem = New GraphicsSystem();
	mpGraphicsSystem->init(width, height);
	
	mpResourceManager = New ResourceManager();
	gpUnitManager = New UnitManager(mpResourceManager);
	setupDependencies();
	gpUnitManager->loadBullets();
	//TODO: Animation for the levels
	
	mpLevelManager = New LevelManager();
	mpLevelManager->loadLevel("../LEVELS/Level1.txt", mpResourceManager);
	mpLevelManager->loadLevel("../LEVELS/Level2.txt", mpResourceManager);
	mpLevelManager->loadLevel("../LEVELS/Level3.txt", mpResourceManager);
	//mpLevelManager->loadLevel("../LEVELS/Level4.txt", mpResourceManager);
	//TODO: construct levels from files
	

	//TODO: start/win/lose screen initializations
	//TODO: add ^ to resource manager
	//Screen states and menus
	mpStartScreen = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/TankStormStartScreenDetails.png", mpGraphicsSystem);
	mpStartOptions = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/StartOptionsMenu.png", mpGraphicsSystem);
	mpGameOptions = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/GameOptionsOverlay.png", mpGraphicsSystem);
	mpHUD = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/HUD.png", mpGraphicsSystem);
	mpWinScreen = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/GameWon.png", mpGraphicsSystem);
	mpLoseScreen = New GraphicsBuffer("../ASSETS/MenuAndStateScreens/GameLost.png", mpGraphicsSystem);
	mpResourceManager->addGraphicsBuffer("mpStartScreen", mpStartScreen);
	mpResourceManager->addGraphicsBuffer("mpStartOptions", mpStartOptions);
	mpResourceManager->addGraphicsBuffer("mpGameOptions", mpGameOptions);
	mpResourceManager->addGraphicsBuffer("mpHUD", mpHUD);
	mpResourceManager->addGraphicsBuffer("mpWinScreen", mpWinScreen);
	mpResourceManager->addGraphicsBuffer("mpLoseScreen", mpLoseScreen);



	//TODO: make game listen for things, like:
	gpEventSystem->addListener(ESC_KEY_EVENT, this);
	gpEventSystem->addListener(TOGGLE_MUSIC_EVENT, mpSoundHandler);
	gpEventSystem->addListener(FIRED_EVENT, mpSoundHandler);
	gpEventSystem->addListener(VOLUME_INCREASE_EVENT, mpSoundHandler);
	gpEventSystem->addListener(VOLUME_DECREASE_EVENT, mpSoundHandler);
	gpEventSystem->addListener(DIFFICULTY_INCREASE_EVENT, this);
	gpEventSystem->addListener(DIFFICULTY_DECREASE_EVENT, this);
	gpEventSystem->addListener(TOGGLE_OPTIONS_EVENT, this);
	gpEventSystem->addListener(ENTER_PRESSED_EVENT, this);
	gpEventSystem->addListener(LOAD_GAME_EVENT, this);
	gpEventSystem->addListener(SAVE_GAME_EVENT, this);
	gpEventSystem->addListener(LEVEL_FAILED_EVENT, this);
	gpEventSystem->addListener(LEVEL_COMPLETE_EVENT, mpLevelManager);
	gpEventSystem->addListener(LEVEL_COMPLETE_EVENT, this);
	gpEventSystem->addListener(ACTIVATE_SE_EVENT, mpSoundHandler);
	gpEventSystem->addListener(DEACTIVATE_SE_EVENT, mpSoundHandler);
	gpEventSystem->addListener(TANK_DESTROYED_EVENT, mpSoundHandler);
	gpEventSystem->addListener(GAME_COMPLETE_EVENT, this);

	mpFont = New Font("../ASSETS/cour.ttf", 18);
	//TODO: mpColor = Color(255, 0, 0, 1);
	mHUDLoc = Vector2D(0, 512);
	mScoreLoc = Vector2D(144, 521);
	mBonusLoc = Vector2D(344, 521);
	mLevelNameLoc = Vector2D(144, 580);
	mLivesLoc = Vector2D(144, 550);
	mOriginPoint = Vector2D(0,0);

	

	srand((Uint32)time(nullptr));

	mpTimer = New Timer();
	mpTimer->start();

	return true;
}

void Game::runLoop()
{
	bool LevelProgress=true;
	mKeepLooping = true;
	Vector2D origin = Vector2D(0,0);

	double FPS = 60.0f;
	double fpsDelay = 1000.0 / FPS;
	double frameTime = 0.0f;

	double currentFPS = 1.0f;
	mpTimer->start();
	
	while(mKeepLooping)
	{
		mpTimer->start();
		//input+Units
		gpGame->update(frameTime);

		//units essentially are what's drawn
		gpGame->draw();

		
		//cout << (float)currentFPS/FPS << endl;

		mpTimer->sleepUntilElapsed(fpsDelay);
		frameTime = mpTimer->getElapsedTime();
		currentFPS = (1000.0 / frameTime);
	}

	cleanup();
}

void Game::setupDependencies()
{
	std::stringstream ss = stringstream();

	//TODO: DATA DRIVEN
	//TODO: dependency GBuffers, don't forget ResourceManager and New
	GraphicsBuffer* floorWall = New GraphicsBuffer("../ASSETS/floorWall2.png", mpGraphicsSystem);
	mpResourceManager->addGraphicsBuffer("floorWall", floorWall);
	//GraphicsBuffer* spriteMap = New GraphicsBuffer("../ASSETS/.png", mpGraphicsSystem);
	//mpResourceManager->addGraphicsBuffer("spriteMap", spriteMap);

	GraphicsBuffer* spriteMap = New GraphicsBuffer("../ASSETS/workingArt/barrel.png", mpGraphicsSystem);
	mpResourceManager->addGraphicsBuffer("BARREL", spriteMap);
	
	spriteMap = New GraphicsBuffer("../ASSETS/workingArt/tanks.png", mpGraphicsSystem);
	mpResourceManager->addGraphicsBuffer("TANKS", spriteMap);

	spriteMap = New GraphicsBuffer("../ASSETS/workingArt/bullet.png", mpGraphicsSystem);
	mpResourceManager-> addGraphicsBuffer("BULLET", spriteMap);

	spriteMap = New GraphicsBuffer("../ASSETS/workingArt/explosion.png", mpGraphicsSystem);
	mpResourceManager-> addGraphicsBuffer("EXPLOSION", spriteMap);

	//TODO: dependency Sprites
	Vector2D tileLocs(0, 0);
	Sprite* floorSprite = New Sprite(floorWall, tileLocs, 32, 32);
	mpResourceManager->addSprite("floorSprite", floorSprite);

	tileLocs.setX(32);
	Sprite* wallSprite = New Sprite(floorWall, tileLocs, 32, 32);
	mpResourceManager->addSprite("wallSprite", wallSprite);

	//Tank Sprites
	Vector2D tankLoc(0, 0);
	Sprite* tankSprites;
	for (int i = 0; i < 8; i++) //green
	{
		tankLoc.setX((float)32 * i);
		ss << "GREEN_TANKS" << i;
		tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("TANKS"), tankLoc, 32, 32);
		mpResourceManager->addSprite(ss.str(), tankSprites);
		ss.str("");
	}
	tankLoc= Vector2D(0,33);

	for (int i = 0; i < 8; i++) //orange
	{
		tankLoc.setX((float)32 * i);
		ss << "ORANGE_TANKS" << i;
		tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("TANKS"), tankLoc, 32, 32);
		mpResourceManager->addSprite(ss.str(), tankSprites);
		ss.str("");
	}


	tankLoc= Vector2D(0,0);
	tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("BARREL"), tankLoc, 25, 14);
	mpResourceManager->addSprite("GREEN_BARREL", tankSprites);
	tankLoc= Vector2D(0,15);
	tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("BARREL"), tankLoc, 25, 14);
	mpResourceManager->addSprite("ORANGE_BARREL", tankSprites);
	//END Tank Sprites

	//Bullet
	tankLoc = Vector2D(0,0);
	tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("BULLET"), tankLoc, 8, 8);
	mpResourceManager->addSprite("BULLET", tankSprites);

	//explosion
	for (int i = 0; i < 3; i++)
	{
		tankLoc.setX((float)32 * i);
		ss << "EXPLOSION" << i;
		tankSprites = New Sprite(mpResourceManager->getGraphicsBuffer("EXPLOSION"), tankLoc, 32, 32);
		mpResourceManager->addSprite(ss.str(), tankSprites);
		ss.str("");
	}
	

	//TODO: Dependency Animations of sprites
	Animation* floorAnimation = New Animation(300, false);
	floorAnimation->addSprite(floorSprite);
	mpResourceManager->addAnimation("AfloorAnimation", floorAnimation);

	Animation* wallAnimation = New Animation(300, false);
	wallAnimation->addSprite(wallSprite);
	mpResourceManager->addAnimation("AwallAnimation", wallAnimation);

	//Tank animations
	Animation* tankAnim = New Animation(300, true);
	for (int i = 7; i >=0; i--)
	{
		ss << "GREEN_TANKS" << i;
		tankAnim->addSprite(mpResourceManager->getSprite(ss.str()));
		ss.str("");
	}
	mpResourceManager->addAnimation("GREEN_TANK",tankAnim);

	tankAnim = New Animation(300, true);
	for (int i = 7; i >=0; i--)
	{
		ss << "ORANGE_TANKS" << i;
		tankAnim->addSprite(mpResourceManager->getSprite(ss.str()));
		ss.str("");
	}
	mpResourceManager->addAnimation("ORANGE_TANK",tankAnim);


	//Bullet Animation
	tankAnim = New Animation(0, false);
	tankAnim->addSprite(mpResourceManager->getSprite("BULLET"));
	mpResourceManager->addAnimation("BULLET",tankAnim);

	//Explosion Animation
	tankAnim = New Animation(300, true);
	for (int i = 0; i < 3; i++)
	{
		ss << "EXPLOSION" << i;
		tankAnim->addSprite(mpResourceManager->getSprite(ss.str()));
		ss.str("");
	}
	mpResourceManager->addAnimation("EXPLOSION",tankAnim);

	//MUSICCSSSSZSZSSSSSZS!!1!1111!1!!!!
	mpSoundHandler->loadAssets();

}


void Game::update(double frameTime)
{
	mpInputManager->update();

	if(mStart || mStartOptions || mWin || mLose || mGameOptions)
		return;
	mpLevelManager->update(frameTime);
	

	gpUnitManager->update((float)frameTime);

	if (mpLevelManager->gameShouldEnd())
	{
		mKeepLooping = false;
	}
	
}

void Game::draw()
{
	mpGraphicsSystem->clearScreen();

	if(mStart)
	{
		mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpStartScreen, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);
		mpGraphicsSystem->flipBuffer();
		return;
	}
	if(mStartOptions)
	{
		mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpStartOptions, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);
		mpGraphicsSystem->flipBuffer();
		return;
	}
	if(mGameOptions)
	{
		gpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpLevelManager->draw(mpGraphicsSystem->getBackBuffer());
		mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpGameOptions, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);
		mpGraphicsSystem->flipBuffer();
		return;
	}
	if(mWin)
	{	
		mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpWinScreen, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);
		mpGraphicsSystem->flipBuffer();
		return;	
	}
	if(mLose)
	{
		mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpLoseScreen, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);
		mpGraphicsSystem->flipBuffer();
		return;	
	}

	//mpGraphicsSystem->getBackBuffer()->drawScaled(mOriginPoint, &Sprite(mpLoseScreen, mOriginPoint, DISPLAY_WIDTH, DISPLAY_HEIGHT), 1.0f);


	
	gpUnitManager->draw(mpGraphicsSystem->getBackBuffer());

	mpLevelManager->draw(mpGraphicsSystem->getBackBuffer());

	//mpGraphicsSystem->getBackBuffer()->drawOrigin(Vector2D(200,400), mpResourceManager->getSprite("ORANGE_TANKS1"));
	//mpGraphicsSystem->getBackBuffer()->drawOrigin(Vector2D(200,400), mpResourceManager->getSprite("GREEN_BARREL"));

	mpGraphicsSystem->getBackBuffer()->drawScaled(mHUDLoc, &Sprite(mpHUD, mOriginPoint, DISPLAY_WIDTH, 88), 1.0f);

	std::stringstream scorestream;
	scorestream << mScore;
	mScoreString = scorestream.str();
	scorestream.str("");
	scorestream << mBonus;
	mBonusString = scorestream.str();
	scorestream.str("");
	scorestream << mLives;
	mLivesString = scorestream.str();

	mpGraphicsSystem->getBackBuffer()->writeText(mScoreLoc, mpFont, mpColor, mScoreString);
	mpGraphicsSystem->getBackBuffer()->writeText(mBonusLoc, mpFont, mpColor, mBonusString);
	mpGraphicsSystem->getBackBuffer()->writeText(mLevelNameLoc, mpFont, mpColor, mLevelNameString);
	mpGraphicsSystem->getBackBuffer()->writeText(mLivesLoc, mpFont, mpColor, mLivesString);


	mpGraphicsSystem->flipBuffer();
}
 

void Game::handleEvent(const Event& theEvent)
{
	//TODO: Change the event handling here to appropriate actions for new game
	
	//ESC is global to every game state
	if(theEvent.getType() == ESC_KEY_EVENT)
	{
		mKeepLooping = false;
	}
	//Event handling for Start state
	if (mStart)
	{	
		if(theEvent.getType() == TOGGLE_OPTIONS_EVENT)
		{
			mStartOptions = true;
			mStart = false;
		}
		if(theEvent.getType() == ENTER_PRESSED_EVENT)
		{
			mStart = false;
			mpLevelManager->nextLevel();
		}
		if(theEvent.getType() == LOAD_GAME_EVENT)
		{
			cout << "LOAD\n";
			loadStats();
			
		}
	}
	//Event handling for StartOptions state
	else if (mStartOptions)
	{
		if(theEvent.getType() == TOGGLE_OPTIONS_EVENT)
		{
			mStartOptions = false;
			mStart = true;
		}

		if(theEvent.getType() == DIFFICULTY_INCREASE_EVENT)
		{
			mpLevelManager->modulateDifficulty(true);
		}

		if(theEvent.getType() == DIFFICULTY_DECREASE_EVENT)
		{
			mpLevelManager->modulateDifficulty(false);
		}
	}
	//Event handling for in-game options state
	else if (mGameOptions)
	{
		if(theEvent.getType() == TOGGLE_OPTIONS_EVENT)
		{
			mGameOptions = false;
		}
		if (theEvent.getType() == SAVE_GAME_EVENT)
		{
			cout << "SAVE\n";
			saveStats();
		}
	}
	//Event handling for Win state
	else if (mWin)
	{
		if(theEvent.getType() == LOAD_GAME_EVENT)
		{
			cout << "LOAD\n";
			loadStats();
		}

		if(theEvent.getType() == ENTER_PRESSED_EVENT)
		{
			mpLevelManager->restart();
			mWin = false;
		}
	}
	//Event handling for Lose state
	else if (mLose)
	{
		if(theEvent.getType() == LOAD_GAME_EVENT)
		{
			cout << "LOAD\n";
			loadStats();
		}

		if(theEvent.getType() == ENTER_PRESSED_EVENT)
		{
			mpLevelManager->restart();
			mLose = false;
		}
	}
	//Event handling for game loop state
	else
	{
		if (theEvent.getType() == GAME_COMPLETE_EVENT)
		{
			mWin = true;
		}
	
		if (theEvent.getType() == LEVEL_COMPLETE_EVENT)
		{
			mWin = true;
		}

		if (theEvent.getType() == LEVEL_FAILED_EVENT)
		{
			mLives--;

			if (mLives <= 0)
			{
				mLose = true;
				mpLevelManager->getCurrentLevel()->cleanup();
			}
			else
			{
				mpLevelManager->getCurrentLevel()->resetLevel();
			}
		}

		if (theEvent.getType() == SAVE_GAME_EVENT)
		{
			cout << "SAVE\n";
			saveStats();
		}
		if (theEvent.getType() == TOGGLE_OPTIONS_EVENT)
		{
			mGameOptions = true;
		}
	}
}

void Game::cleanup()
{
	if (mpLevelManager)
		mpLevelManager->cleanup();
	//if (gpUnitManager)
		//gpUnitManager->deleteAll();

	delete mpFont;
	mpFont = nullptr;

	delete mpResourceManager;
	mpResourceManager = nullptr;

	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	delete mpInputManager;
	mpInputManager = nullptr;

	delete mpLevelManager;
	mpLevelManager = nullptr;

	delete mpSoundHandler;
	mpSoundHandler = nullptr;

	

}

void Game::setLevelName(string name)
{
	stringstream ss;
	ss << name;
	mLevelNameString = ss.str();
}

void Game::saveStats()
{
	ofstream saveFile;
	saveFile.open(SAVE_FILE_STAT);
	saveFile << mLives << endl;
	saveFile << mScore;

}

void Game::loadStats()
{
	ifstream loadFile;
	loadFile.open(SAVE_FILE_STAT);

	if(loadFile)
	{
		loadFile >> mLives;
		loadFile >> mScore;

		
		mStart = false;
		mStartOptions = false;
		mWin = false;
		mLose = false;
		mGameOptions = false;

	}

}

int Game::getDiffLevel()
{
	return mDifficultyLevel;
}
