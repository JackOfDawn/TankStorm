/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Snake.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once

#include "Game.h"
#include <string>
#include <vector>
#include "Trackable.h"
#include "Unit.h"
#include "MiscDataDef.h"

class Sprite;
class Unit;
class GridUnit;
class LevelManager;

using std::vector;

const double SNAKE_MIN_SPEED = 100;
const double SNAKE_MAX_SPEED = 2000;
const double SPEED_CHANGE_FACTOR = 100;

class Snake : public EventListener
{
public:
	Snake(int x, int y, Animation* animation, int startingLength, double timePerMove, int levelNum);
	virtual ~Snake();

	void ateFood();
	void draw(GraphicsBuffer* targetBuffer);
	void setDirection(Direction newDirection);	
	void slowDown();
	void speedUp();
	void update(double passedTime);		//TODO

	//inline accessors
	inline vector<GridUnit*> getSegments() const {return mpSnakeSegments;};
	inline int getNumSegments() const {return mTargetSnakeSize;}

	//necessities
	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "Snake"; }

	inline GridUnit * getSnakeHead( void ) const { return mpSnakeHead; }

private:
	GridUnit *mpSnakeHead;

	Direction mDirection;
	vector<GridUnit*> mpSnakeSegments;

	void addSegment();
	void moveSnake();	//TODO??
	void tileInteraction();

	int mTargetSnakeSize;
	int mMovementTime;
	double mTimeUntilMove;
};











