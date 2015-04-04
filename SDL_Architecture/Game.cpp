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
#include <SDL.h>
#include <time.h>

Game::Game(void)
	:mpColor(255,0,0,255)
{
	mpGraphicsSystem = NULL;
	mpInputManager = NULL;
	mpResourceManager = NULL;
	mpLevelManager = NULL;
	mpFont = NULL;
	mHUDLoc = NULL;
	mOriginPoint = NULL;

	mStart = true;
	mWin = false;
	mLose = false;

	mScore = 0;
	mNeedClean = false;
	mKeepLooping = true;
}

Game::~Game(void)
{
	cleanup();
}

bool Game::init(int width, int height)
{
	
	mScore = 0;

	mpInputManager = New InputManager();
	mpInputManager->init();

	mpGraphicsSystem = New GraphicsSystem();
	mpGraphicsSystem->init(width, height);
	
	mpResourceManager = New ResourceManager();
	gpUnitManager = New UnitManager(mpResourceManager);
	setupDependencies();

	Animation* head = mpResourceManager->getAnimation("headAnimation");

	mpLevelManager = New LevelManager();
	mpLevelManager->loadLevel("Levels/Level1.txt", head, mpResourceManager);
	mpLevelManager->loadLevel("Levels/Level2.txt", head, mpResourceManager);
	mpLevelManager->loadLevel("Levels/Level3.txt", head, mpResourceManager);
	mpLevelManager->nextLevel();

	mpStartScreen = New GraphicsBuffer("Assets/startscreen.png", mpGraphicsSystem);
	mpWinScreen = New GraphicsBuffer("Assets/winscreen.png", mpGraphicsSystem);
	mpLoseScreen = New GraphicsBuffer("Assets/losescreen.png", mpGraphicsSystem);
	mpResourceManager->addGraphicsBuffer("startscreen", mpStartScreen);
	mpResourceManager->addGraphicsBuffer("winscreen", mpWinScreen);
	mpResourceManager->addGraphicsBuffer("losescreen", mpLoseScreen);


	gpEventSystem->addListener(ESC_KEY_EVENT, this);
	gpEventSystem->addListener(SPACE_BAR_EVENT, this);
	gpEventSystem->addListener(ADD_POINTS_EVENT, this);
	gpEventSystem->addListener(LEVEL_FAILED_EVENT, this);
	gpEventSystem->addListener(LEVEL_COMPLETE_EVENT, this);

	mpFont = New Font("Assets/cour.ttf", 24);
	mpColor = Color(255, 0, 0, 1);
	mHUDLoc = Vector2D(0, 0);
	mOriginPoint = Vector2D(0,0);

	srand((Uint32)time(NULL));

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

		//unit draw, so... Grid?
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
	//GBuffer of tiles
	GraphicsBuffer* tileMap = New GraphicsBuffer("assets/SnakeSpritemap.png", mpGraphicsSystem);
	GraphicsBuffer* movingAnimationsMap = New GraphicsBuffer("assets/pickups.png", mpGraphicsSystem);
	
	mpResourceManager->addGraphicsBuffer("tiles", tileMap);
	mpResourceManager->addGraphicsBuffer("movingThings", movingAnimationsMap);

	//Sprites of tiles
	Vector2D tileLocs(0, 0);
	Sprite* headSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("headSprite", headSprite);

	tileLocs.setX(30);
	Sprite* bodySprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("bodySprite", bodySprite);

	/*tileLocs.setX(60);
	Sprite* basicFoodSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("basicFoodSprite", basicFoodSprite);

	tileLocs.setX(90);
	Sprite* speedFoodSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
		mpResourceManager->addSprite("speedFoodSprite", speedFoodSprite);

	tileLocs.setX(120);
	Sprite* slowFoodSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("slowFoodSprite", slowFoodSprite);*/

	//speedup
	tileLocs.setX(0);
	Sprite* speedFoodSprite1 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("speedFoodSprite1", speedFoodSprite1);
	tileLocs.setX(30);
	Sprite* speedFoodSprite2 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("speedFoodSprite2", speedFoodSprite2);
	tileLocs.setX(60);
	Sprite* speedFoodSprite3 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("speedFoodSprite3", speedFoodSprite3);
	tileLocs.setX(90);
	Sprite* speedFoodSprite4 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("speedFoodSprite4", speedFoodSprite4);
	
	//slowdown
	tileLocs.setY(30);
	tileLocs.setX(0);
	Sprite* slowFoodSprite1 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("slowFoodSprite1", slowFoodSprite1);
	tileLocs.setX(30);
	Sprite* slowFoodSprite2 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("slowFoodSprite2", slowFoodSprite2);
	tileLocs.setX(60);
	Sprite* slowFoodSprite3 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("slowFoodSprite3", slowFoodSprite3);
	tileLocs.setX(90);
	Sprite* slowFoodSprite4 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("slowFoodSprite4", slowFoodSprite4);

	//basic food
	tileLocs.setY(60);
	tileLocs.setX(0);
	Sprite* basicFoodSprite1 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("basicFoodSprite1", basicFoodSprite1);
	tileLocs.setX(30);
	Sprite* basicFoodSprite2 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("basicFoodSprite2", basicFoodSprite2);
	tileLocs.setX(60);
	Sprite* basicFoodSprite3 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("basicFoodSprite3", basicFoodSprite3);
	tileLocs.setX(90);
	Sprite* basicFoodSprite4 = New Sprite(movingAnimationsMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("basicFoodSprite4", basicFoodSprite4);

	tileLocs.setY(0);
	tileLocs.setX(150);
	Sprite* floorSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("floorSprite", floorSprite);

	tileLocs.setX(180);
	Sprite* wallSprite = New Sprite(tileMap, tileLocs, CELL_DIMENSION, CELL_DIMENSION);
	mpResourceManager->addSprite("wallSprite", wallSprite);

	//Animations of sprites
	Animation* headAnimation = New Animation(300, false);
	headAnimation->addSprite(headSprite);
	mpResourceManager->addAnimation("headAnimation", headAnimation);

	Animation* bodyAnimation = New Animation(300, false);
	bodyAnimation->addSprite(bodySprite);
	mpResourceManager->addAnimation("bodyAnimation", bodyAnimation);

	Animation* basicFoodAnimation = New Animation(300, true);
	basicFoodAnimation->addSprite(basicFoodSprite1);
	basicFoodAnimation->addSprite(basicFoodSprite2);
	basicFoodAnimation->addSprite(basicFoodSprite3);
	basicFoodAnimation->addSprite(basicFoodSprite4);
	mpResourceManager->addAnimation("basicFoodAnimation", basicFoodAnimation);
	
	Animation* speedFoodAnimation = New Animation(300, true);
	speedFoodAnimation->addSprite(speedFoodSprite1);
	speedFoodAnimation->addSprite(speedFoodSprite2);
	speedFoodAnimation->addSprite(speedFoodSprite3);
	speedFoodAnimation->addSprite(speedFoodSprite4);
	mpResourceManager->addAnimation("speedFoodAnimation", speedFoodAnimation);
	
	Animation* slowFoodAnimation = New Animation(300, true);
	slowFoodAnimation->addSprite(slowFoodSprite1);
	slowFoodAnimation->addSprite(slowFoodSprite2);
	slowFoodAnimation->addSprite(slowFoodSprite3);
	slowFoodAnimation->addSprite(slowFoodSprite4);
	mpResourceManager->addAnimation("slowFoodAnimation", slowFoodAnimation);
	
	Animation* floorAnimation = New Animation(300, false);
	floorAnimation->addSprite(floorSprite);
	mpResourceManager->addAnimation("floorAnimation", floorAnimation);
	
	Animation* wallAnimation = New Animation(300, false);
	wallAnimation->addSprite(wallSprite);
	mpResourceManager->addAnimation("wallAnimation", wallAnimation);

}


void Game::update(double frameTime)
{
	mpInputManager->update();

	if(mStart || mWin || mLose)
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

	gpUnitManager->draw(mpGraphicsSystem->getBackBuffer());

	mpLevelManager->draw(mpGraphicsSystem->getBackBuffer());

	std::stringstream scorestream;
	scorestream << mScore;
	mScoreString = scorestream.str();

	mpGraphicsSystem->getBackBuffer()->writeText(mHUDLoc, mpFont, mpColor, mScoreString);

	mpGraphicsSystem->flipBuffer();
}
 

void Game::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == ESC_KEY_EVENT)
	{
		mKeepLooping = false;
	}
	if (theEvent.getType() == GAME_COMPLETE_EVENT)
	{
		mKeepLooping = false;
	}
	if (theEvent.getType() == ADD_POINTS_EVENT)
	{
		mScore += mpLevelManager->getCurrentLevel()->getPointsPerFood();
		cout << mScore << endl;
	}
	if (theEvent.getType() == SPACE_BAR_EVENT)
	{
		if(mStart)
			mStart = false;
		else if(mWin)
		{
			mWin = false;
			mpLevelManager->restart();
			mScore = 0;
		}
		else if (mLose)
		{
			mLose = false;
			mpLevelManager->restart();
			mScore = 0;
		}
	}
	if (theEvent.getType() == LEVEL_FAILED_EVENT)
	{
		mLose = true;
	}
	if (theEvent.getType() == LEVEL_COMPLETE_EVENT)
	{
		mWin = true;
	}
}

void Game::cleanup()
{
	if (mpLevelManager)
		mpLevelManager->cleanup();

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

	

}
