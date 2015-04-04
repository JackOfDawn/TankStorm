/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Level.cpp
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#include "Vector2D.h"
#include "Level.h"
#include "Snake.h"
#include "GridUnit.h"
#include "Animation.h"
#include <fstream>
#include "UnitManager.h"
#include "ResourceManager.h"
#include "UpPressedEvent.h"
#include "DownPressedEvent.h"
#include "LeftPressedEvent.h"
#include "RightPressedEvent.h"
#include <time.h>

using namespace std;

Level::Level(int levelNum)
{
	mSpeed = 0;
	mStartingSegments = 0;
	mTargetSegments = 0;
	mPointsPerFood = 0;
	mSpeedUpChance = 0;
	mSlowDownChance = 0;
	mLevelNum = levelNum;
	mpSnake = nullptr;
	mFoodSpawned = false;
	mModOnTheScreen = false;
	mTimeBetweenModSpawn = 5000;
	mModTimeout = mTimeBetweenModSpawn;
}

Level::~Level()
{
	
}

void Level::loadFromFile(std::string sourcePath, Animation* head, ResourceManager* pResourceManager)
{
	fstream fileStream( sourcePath );

	while(!fileStream.eof())
	{
		fileStream >> mSpeed;
		fileStream >> mStartingSegments;
		fileStream >> mTargetSegments;
		fileStream >> mPointsPerFood;
		fileStream >> mSpeedUpChance;
		fileStream >> mSlowDownChance;

		for( int i = 0; i < 18; i++ )
		{
			for( int j = 0; j < 32; j++ )
			{
				fileStream >> mGrid[j][i];
			}
		}

	}

	mpHeadAnim = head;
	mpResources = pResourceManager;
}

bool Level::isCurrentSpaceSafe()
{
	GridUnit* pSnakeHead = mpSnake->getSnakeHead();

	int snakeX = pSnakeHead->getGridPosX();
	int snakeY = pSnakeHead->getGridPosY();

	if (snakeX < 0 || snakeX >= GRID_WIDTH)
		return false;

	if (snakeY < 0 || snakeY >= GRID_HEIGHT)
		return false;
	
	//check if this is a wall
	if(mGrid[snakeX][snakeY] == 3)
		return false;
	
	//is this part of the snake?
	for (int i = 1; i < (signed)mpSnake->getSegments().size(); i++)
	{
		if (mpSnake->getSegments()[i]->getGridPosX() == snakeX && mpSnake->getSegments()[i]->getGridPosY() == snakeY)
		{
			gpEventSystem->fireEvent(LEVEL_FAILED_EVENT);
			return false;
		}
	}

	//is this food?
	if(mGrid[snakeX][snakeY] == 4)
	{
		mpSnake->ateFood();
		mFoodSpawned = false;
		mGrid[snakeX][snakeY] = 0;
		string tileID = "tile";
		tileID +=snakeX;
		tileID +=snakeY;
		gpEventSystem->fireEvent(ADD_POINTS_EVENT);
		gpUnitManager->findUnit(tileID)->changeAnimation(mpResources->getAnimation("floorAnimation"));
		return true;
	}
	
	//is this a mod cell?
	if(mGrid[snakeX][snakeY] == 5)
	{
		//speed up
		gpEventSystem->fireEvent(SPEED_SNAKE_EVENT);
		gpGame->addPoints(20);
		mGrid[snakeX][snakeY] = 0;
		string tileID = "tile";
		tileID +=snakeX;
		tileID +=snakeY;
		gpUnitManager->findUnit(tileID)->changeAnimation(mpResources->getAnimation("floorAnimation"));
		mModOnTheScreen = false;
		return true;
	}
	else if(mGrid[snakeX][snakeY] == 6)
	{
		gpEventSystem->fireEvent(SLOW_SNAKE_EVENT);
		gpGame->addPoints(-50);
		mGrid[snakeX][snakeY] = 0;
		string tileID = "tile";
		tileID +=snakeX;
		tileID +=snakeY;
		gpUnitManager->findUnit(tileID)->changeAnimation(mpResources->getAnimation("floorAnimation"));
		mModOnTheScreen = false;
		return true;
	}
	
	return true;

}

void Level::setup()
{
	string snakeId;
	snakeId = "snake" + mLevelNum;

	makeGridUnits();

	mpSnake = New Snake(1, 16, mpHeadAnim, mStartingSegments, mSpeed, mLevelNum);

	gpEventSystem->addListener(UP_ARROW_EVENT, mpSnake);
	gpEventSystem->addListener(DOWN_ARROW_EVENT, mpSnake);
	gpEventSystem->addListener(LEFT_ARROW_EVENT, mpSnake);
	gpEventSystem->addListener(RIGHT_ARROW_EVENT, mpSnake);
	gpEventSystem->addListener(SPEED_SNAKE_EVENT, mpSnake);
	gpEventSystem->addListener(SLOW_SNAKE_EVENT, mpSnake);

	
}

void Level::cleanup()
{
	delete mpSnake;
	mpSnake = nullptr;

	for (int i = 0; i < (signed)mGridTileUnits.size(); i++)
	{
		gpUnitManager->removeSpecific(mGridTileUnits[i]);
		delete mGridTileUnits[i];
	}
	mGridTileUnits.clear();

}

void Level::update(double passedTime)
{
	mpSnake->update(passedTime);

	consumablesManagement(passedTime);
}

void Level::makeGridUnits()
{
	for( int i = 0; i < 18; i++ )
	{
		for( int j = 0; j < 32; j++ )
		{
			string tileID = "tile";
				   tileID += j;
				   tileID += i;
			GridUnit* tileUnit = nullptr;
			Animation* tileAnimation;

			switch( mGrid[j][i] )
			{
			case 0:
				tileAnimation = mpResources->getAnimation("floorAnimation");
				tileUnit = New GridUnit(j, i, tileAnimation, FLOOR_CELL_TYPE);
				gpUnitManager->addUnit(tileID, tileUnit);
				break;
			case 3:
				tileAnimation = mpResources->getAnimation("wallAnimation");
				tileUnit = New GridUnit(j, i, tileAnimation, WALL_CELL_TYPE);
				gpUnitManager->addUnit(tileID, tileUnit);
			}
			if(tileUnit != nullptr)
				mGridTileUnits.push_back(tileUnit);
		}
	}


}

void Level::draw(GraphicsBuffer* targetBuffer)
{
	mpSnake->draw(targetBuffer);
}

void Level::consumablesManagement(double passedTime)
{
	int x, y;
	bool snakePiece = true;
	
	//regular food
	while(!mFoodSpawned)
	{
		x = (rand()%30) + 1;
		y = (rand()%16) + 1;

		if(mGrid[x][y] == 0)
		{
			snakePiece = false;
			for (int i = 0; i < (signed)mpSnake->getSegments().size(); i++)
			{
				if (mpSnake->getSegments()[i]->getGridPosX() == x && mpSnake->getSegments()[i]->getGridPosY() == y)
				{
					snakePiece = true;
				}
			}

			if (!snakePiece)
			{
				string findGridUnit = "tile";
				findGridUnit += x;
				findGridUnit += y;

				mGrid[x][y] = 4;

				gpUnitManager->findUnit(findGridUnit)->changeAnimation(mpResources->getAnimation("basicFoodAnimation"));

				mFoodSpawned = true;

				break;
			}
		}
	}

	//mods
	double speedChance = mSpeedUpChance * 100;
	double slowChance = mSlowDownChance * 100;

	mModTimeout -= passedTime;
	if (mModTimeout <= 0)
	{
		mModTimeout = mTimeBetweenModSpawn;
		while(!mModOnTheScreen)
		{
			x = (rand()%30) + 1;
			y = (rand()%16) + 1;

			if(mGrid[x][y] == 0)
			{
				snakePiece = false;
				for (int i = 0; i < (signed)mpSnake->getSegments().size(); i++)
				{
					if (mpSnake->getSegments()[i]->getGridPosX() == x && mpSnake->getSegments()[i]->getGridPosY() == y)
					{
						snakePiece = true;
					}
				}

				if (!snakePiece)
				{
					string findGridUnit = "tile";
					findGridUnit += x;
					findGridUnit += y;

					int chanceTotal = speedChance+slowChance;
					
					int randomNum = rand()%chanceTotal;
					if(randomNum < speedChance)
					{
						mGrid[x][y] = 5;
						gpUnitManager->findUnit(findGridUnit)->changeAnimation(mpResources->getAnimation("speedFoodAnimation"));
					}	
					else
					{
						mGrid[x][y] = 6;
						gpUnitManager->findUnit(findGridUnit)->changeAnimation(mpResources->getAnimation("slowFoodAnimation"));	
					}

					mModOnTheScreen = true;

					break;
				}

			}
		}
	}

}
