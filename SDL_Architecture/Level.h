/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		Level.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once

#include "Trackable.h"
#include <vector>
#include "Vector2D.h"
#include "GridUnit.h"

class Snake;
class Animation;
class ResourceManager;

const int GRID_WIDTH  = 32;
const int GRID_HEIGHT = 18;

class Level : public TrackableObject
{
public:
	Level(int levelNum);
	virtual ~Level();

	void loadFromFile(std::string sourcePath, Animation* head, ResourceManager* pResourceManager);
	bool isCurrentSpaceSafe();
	void setup();
	void cleanup();
	void draw(GraphicsBuffer* targetBuffer);
	void update(double passedTime);

	//accessors
	inline Snake* const getSnake(){return mpSnake;}
	inline int const getSpeed(){return mSpeed;}
	inline int const getStartingSegments(){return mStartingSegments;}
	inline int const getTargetSegments(){return mTargetSegments;}
	inline int const getPointsPerFood(){return mPointsPerFood;}
	inline double const getSpeedFreq(){return mSpeedUpChance;}
	inline double const getSlowFreq(){return mSlowDownChance;}

	virtual inline std::string getClassName( void ) const {return "Level";}

private:
	int			mGrid[GRID_WIDTH][GRID_HEIGHT];
	Vector2D*	snakeStartPosition;
	Snake*		mpSnake;
	int			mSpeed,
				mStartingSegments,
				mTargetSegments,
				mPointsPerFood,
				mLevelNum;
	double		mSpeedUpChance,
				mSlowDownChance;
	Animation*	mpHeadAnim;
	ResourceManager* mpResources;
	std::vector<GridUnit*> mGridTileUnits;
	
	bool		mFoodSpawned,
				mModOnTheScreen;

	double		mTimeBetweenModSpawn,
				mModTimeout;
	

	void		makeGridUnits();
	void		consumablesManagement(double passedTime);

};