/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Snake.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#include "Snake.h"
#include "Event.h"
#include "GridUnit.h"
#include "Game.h"
#include "LevelManager.h"
#include <sstream>
#include "UnitManager.h"
#include "ResourceManager.h"



Snake::Snake(int x, int y, Animation* animation, int startingLength, double moveTime, int levelNum)
{
	//Snake itself
	mDirection = DIRECTION_RIGHT;
	mTargetSnakeSize = startingLength;
	mMovementTime = moveTime;
	mTimeUntilMove = mMovementTime;

	//Head
	string headNum;
	headNum = "snakeHead"+levelNum;
	mpSnakeHead = New GridUnit(x, y, animation, HEAD_CELL_TYPE);
	mpSnakeSegments.push_back(mpSnakeHead);
	gpUnitManager->addUnit(headNum, mpSnakeHead);
}

Snake::~Snake()
{
	for (int i = 0; i < (signed)mpSnakeSegments.size(); ++i)
	{
		GridUnit* pSegment = mpSnakeSegments[i];

		gpUnitManager->removeSpecific(pSegment);
		delete pSegment;
	}
}

void Snake::addSegment()
{
	stringstream sstream;
	sstream << "Segment" << mpSnakeSegments.size();
	
	GridUnit* newSeg = New GridUnit(0, 0, gpGame->accessResourceManager()->getAnimation("bodyAnimation"), BODY_CELL_TYPE);
	gpUnitManager->addUnit(sstream.str(), newSeg);

	mpSnakeSegments.push_back(newSeg);

}

void Snake::ateFood()
{
	mTargetSnakeSize++;
}

void Snake::update(double passedTime)
{
	mTimeUntilMove -= passedTime;
	
	if(mTimeUntilMove <= 0)
	{
		moveSnake();
		mTimeUntilMove = mMovementTime;
	}

	tileInteraction();

}

void Snake::setDirection(Direction newDirection)
{
	//make sure the snake's new direction doesn't double back on itself
	switch(mDirection)
	{
	case DIRECTION_UP:
		if (newDirection == DIRECTION_DOWN)
		{
			return;
		}
		break;
	case DIRECTION_DOWN:
		if (newDirection == DIRECTION_UP)
		{
			return;
		}
		break;
	case DIRECTION_LEFT:
		if (newDirection == DIRECTION_RIGHT)
		{
			return;
		}
		break;
	case DIRECTION_RIGHT:
		if (newDirection == DIRECTION_LEFT)
		{
			return;
		}
		break;
	}


	mDirection = newDirection;

}



void Snake::speedUp()
{
	mMovementTime -= SPEED_CHANGE_FACTOR;
	if(mMovementTime < SNAKE_MIN_SPEED)
		mMovementTime = SNAKE_MIN_SPEED;
}

void Snake::slowDown()
{
	mMovementTime += SPEED_CHANGE_FACTOR;
	if(mMovementTime > SNAKE_MAX_SPEED)
		mMovementTime = SNAKE_MAX_SPEED;
}

void Snake::moveSnake()
{
	if((unsigned)mTargetSnakeSize > mpSnakeSegments.size())
	{
		addSegment();
	}

	for (int i = mpSnakeSegments.size()-1; i > 0; i--)
	{
		mpSnakeSegments[i]->setPosition(mpSnakeSegments[i-1]->getX(), mpSnakeSegments[i-1]->getY());
	}

	int currX = mpSnakeSegments[0]->getX(),
		currY = mpSnakeSegments[0]->getY();
	
	switch(mDirection)
	{
	case DIRECTION_UP:
		mpSnakeSegments[0]->setPosition(currX, currY-1);
		break;
	case DIRECTION_DOWN:
		mpSnakeSegments[0]->setPosition(currX, currY+1);
		break;
	case DIRECTION_LEFT:
		mpSnakeSegments[0]->setPosition(currX-1, currY);
		break;
	case DIRECTION_RIGHT:
		mpSnakeSegments[0]->setPosition(currX+1, currY);
		break;
	}

}

void Snake::handleEvent(const Event& theEvent)
{
	switch(theEvent.getType())
	{
	case UP_ARROW_EVENT :
		setDirection(DIRECTION_UP);
		break;
	case DOWN_ARROW_EVENT:
		setDirection(DIRECTION_DOWN);
		break; 
	case LEFT_ARROW_EVENT:
		setDirection(DIRECTION_LEFT);
		break;
	case RIGHT_ARROW_EVENT:
		setDirection(DIRECTION_RIGHT);
		break;
	case SPEED_SNAKE_EVENT:
		speedUp();
		break;
	case SLOW_SNAKE_EVENT:
		slowDown();
		break;

	}



}

void Snake::tileInteraction()
{
	/*int snakeX = mpSnakeHead->getGridPosX();
	int snakeY = mpSnakeHead->getGridPosY();

	int currentTile = mpGrid
*/

}

void Snake::draw(GraphicsBuffer* targetBuffer)
{
	for (int i = 0; i < (signed)mpSnakeSegments.size(); i++)
	{
		mpSnakeSegments[i]->draw(targetBuffer);
	}
}

