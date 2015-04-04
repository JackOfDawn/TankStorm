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
#include "Unit.h"
#include "GraphicsBuffer.h"
#include "PlayerTank.h"
#include "AITank.h"

class Bullet;
class GridUnit;
class Animation;
class ResourceManager;

const int GRID_WIDTH  = 25;
const int GRID_HEIGHT = 16;

class Level : public TrackableObject
{
public:
	Level(int levelNum);
	virtual ~Level();

	void loadFromFile(std::string sourcePath, ResourceManager* pResourceManager);
	void setup();
	void resetLevel();
	void cleanup();
	void draw(GraphicsBuffer* targetBuffer);
	void update(double passedTime);

	void handleCollisions();
	void collisionsPlayer();
	void collisionsEnemies();
	void collisionsBullets();

	//accessors
	inline int const getSpeed(){return mSpeed;}
	inline int const getNumEnemies(){return storedNumTanks;}
	inline bool const getTanksLeft(){return mTanksLeft;}

	virtual inline std::string getClassName( void ) const {return "Level";}

	inline std::string getLevelName(){return mLevelName;}

	void saveLevel(std::ofstream& file);
	void loadSave(std::ifstream& file,  ResourceManager* pResourceManager);

private:
	int			mGrid[GRID_WIDTH][GRID_HEIGHT];
	Vector2D*	spawnPosition;

	static const int NUM_TANKS = 5;
	PlayerTank* mpPlayer;
	AITank*		mpEnemyTanks[NUM_TANKS];
	int			tankTypes[NUM_TANKS];
	int			mSpeed,
				mNumEnemies,
				storedNumTanks,
				mLevelNum;
	bool		mTanksLeft;
	Vector2D	mPlayerSpawn;
	std::vector<Vector2D> mEnemySpawn;
	int			mLevelBonus;
	float		mBonusTimer;
//	Animation*	mpHeadAnim;
	ResourceManager* mpResources;
	std::vector<GridUnit*> mWallTileUnits;
	std::vector<GridUnit*> mFloorTileUnits;
	
	void		makeGridUnits();
	void		makePlayerTank();
	void		makeEnemyTank(int i);
//	void		consumablesManagement(double passedTime);

	void		handleCollisionBulletWall(Bullet* bullet, GridUnit* wall);

	std::string	mLevelName;
	

};