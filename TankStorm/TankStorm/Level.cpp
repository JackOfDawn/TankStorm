/*	Author:		Spencer Martin & Jack Storm
 *	Class:		EGP 310-02
 *	Assignment:	Final Tank Storm
 *	File:		Level.cpp
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#include "Vector2D.h"
#include "Level.h"
#include "GridUnit.h"
#include "Animation.h"
#include "UnitManager.h"
#include "ResourceManager.h"
#include "Tank.h"
#include "PlayerTank.h"
#include "AITank.h"
#include "Bullet.h"
#include "Game.h"
#include "LevelCompleteEvent.h"
//#include "UpPressedEvent.h"
//#include "DownPressedEvent.h"
//#include "LeftPressedEvent.h"
//#include "RightPressedEvent.h"
#include <time.h>
#include <fstream>
#include "LevelFailedEvent.h"
#include "TankDestroyedEvent.h"

using namespace std;

Level::Level(int levelNum)
{
	mSpeed = 0;

	mLevelNum = levelNum;

}

Level::~Level()
{
	cleanup();
}

void Level::loadFromFile(std::string sourcePath, ResourceManager* pResourceManager)
{
	//TODO:: Read in multiple tanks and their respective ai
	fstream fileStream( sourcePath );
	int x, y;
	mpResources = pResourceManager;
	while(!fileStream.eof())
	{
		//name
		getline(fileStream, mLevelName);
		//player
		fileStream >> x;
		fileStream >> y;
		mPlayerSpawn = Vector2D((float)x,(float) y);

		fileStream >> storedNumTanks;
		mNumEnemies = storedNumTanks;

		for(int i = 0; i<storedNumTanks; i++)
		{
			fileStream >> x;
			fileStream >> y;
			fileStream >> tankTypes[i];
			mEnemySpawn.push_back(Vector2D((float)x,(float) y)); 
			//Vector2D spawn = Vector2D(mEnemySpawn.getX() * 32 - 16, mEnemySpawn.getY() * 32 - 16);
			//AITank* enemyTank = New AITank(spawn, mpResources->getAnimation("ORANGE_TANK"), mpResources->getSprite("ORANGE_BARREL"), 3);
			//mpEnemyTanks[i] = enemyTank; 
		}
		

		for( int i = 0; i < GRID_HEIGHT; i++ )
		{
			for( int j = 0; j < GRID_WIDTH; j++ )
			{
				fileStream >> mGrid[j][i];
			}
		}

	}

	
}


void Level::setup()
{
	/*string snakeId;
	snakeId = "snake" + mLevelNum;*/
	gpGame->setLevelName(mLevelName);
	makeGridUnits();
	mLevelBonus = 500;
	mBonusTimer = 1000;
	for (int i = storedNumTanks; i < NUM_TANKS; i++)
	{
		
		mpEnemyTanks[i] = nullptr;
	}

	makePlayerTank();
	for(int i = 0; i < storedNumTanks; i++)
	{
		makeEnemyTank(i);
	}
	
}

void Level::cleanup()
{
	
	if(mpPlayer != nullptr)
	{
		gpUnitManager->removeSpecific(mpPlayer);
		
		mpPlayer = nullptr;
	}

	for (int i = 0; i < NUM_TANKS; i++)
	{
	
		if(mpEnemyTanks[i] != nullptr)
		{
			gpUnitManager->removeSpecific(mpEnemyTanks[i]);
			

			
			mpEnemyTanks[i] = nullptr;
			
			//mpEnemyTanks[i] = nullptr;
		}
	}


	for (int i = 0; i < (signed)mWallTileUnits.size(); i++)
	{
		gpUnitManager->removeSpecific(mWallTileUnits[i]);
	
		mWallTileUnits[i] = nullptr;
	}
	mWallTileUnits.clear();

	for (int i = 0; i < (signed)mFloorTileUnits.size(); i++)
	{
		gpUnitManager->removeSpecific(mFloorTileUnits[i]);
		
		mFloorTileUnits[i] = nullptr;
	}
	mFloorTileUnits.clear();


	int i = -1;
	while(gpUnitManager->getBullet(i + 1) != nullptr)
	{
		i++;
		gpUnitManager->getBullet(i)->disable();
	}

}

void Level::resetLevel()
{
	cleanup();
	setup();
}


void Level::update(double passedTime)
{
	//mpSnake->update(passedTime);

	mBonusTimer -= (float)passedTime;
	if(mBonusTimer < 0)
	{
		mBonusTimer = 1000;
		mLevelBonus -= 10;
		if(mLevelBonus <= 0)
		{
			mLevelBonus = 0;
		}

		gpGame->setBonus(mLevelBonus);
	}
	handleCollisions();
	//consumablesManagement(passedTime);
	
	if(mpPlayer == nullptr)
	{
		//cleanup();
	}

	mTanksLeft = false;
	for (int i = 0; i < NUM_TANKS; i++)
	{
		
		if (mpEnemyTanks[i] != nullptr)
		{
				mTanksLeft = true;
				break;
		}
	}
	

}

void Level::makeGridUnits()
{
	for( int i = 0; i < GRID_HEIGHT; i++ )
	{
		for( int j = 0; j < GRID_WIDTH; j++ )
		{
			string tileID = "tile";
				   tileID += j;
				   tileID += i;
			GridUnit* tileUnit = nullptr;
			Animation* tileAnimation;

			switch( mGrid[j][i])
			{
			case 1:
				tileAnimation = mpResources->getAnimation("AwallAnimation");
				tileUnit = New GridUnit(j, i, tileAnimation, WALL_CELL_TYPE);
				gpUnitManager->addUnit(tileID, tileUnit);
				break;
			default:
				tileAnimation = mpResources->getAnimation("AfloorAnimation");
				tileUnit = New GridUnit(j, i, tileAnimation, FLOOR_CELL_TYPE);
				gpUnitManager->addUnit(tileID, tileUnit);
			}
			if(tileUnit != nullptr && tileUnit->getType() == UNIT_TYPES[WALL])
				mWallTileUnits.push_back(tileUnit);
			else if(tileUnit != nullptr && tileUnit->getType() == UNIT_TYPES[FLOOR])
				mFloorTileUnits.push_back(tileUnit);
		}
	}
}

void Level::makePlayerTank()
{
	Vector2D spawn = Vector2D(mPlayerSpawn.getX() * 32 - 16, mPlayerSpawn.getY() * 32 - 16);
	PlayerTank* playerTank = New PlayerTank(spawn, mpResources->getAnimation("GREEN_TANK"), mpResources->getSprite("GREEN_BARREL"));
	gpUnitManager->addUnit("zPLAYER", playerTank);
	playerTank->setMapName("zPLAYER");
	mpPlayer = playerTank;
}

void Level::makeEnemyTank(int i)
{

	Vector2D spawn = Vector2D(mEnemySpawn[i].getX() * 32 - 16, mEnemySpawn[i].getY() * 32 - 16);
	AITank* enemyTank = New AITank(spawn, mpResources->getAnimation("ORANGE_TANK"), mpResources->getSprite("ORANGE_BARREL"), tankTypes[i]);
	mpEnemyTanks[i] = enemyTank; 

	stringstream ss;
	ss << "zENEMY";
	ss << i;
	string name;
	name = ss.str();
	gpUnitManager->addUnit(name, mpEnemyTanks[i]);
	mpEnemyTanks[i]->setMapName(name);
}

void Level::draw(GraphicsBuffer* targetBuffer)
{
	//mpSnake->draw(targetBuffer);
}

void Level::handleCollisions()
{
	collisionsPlayer();
	collisionsEnemies();
	collisionsBullets();
}

void Level::collisionsPlayer()
{
	if(mpPlayer)
	{
		//Unit* collider;
		Bullet* pBCollider;
		bool collision = false;

		int i = -1;
		while(gpUnitManager->getBullet(i + 1) && !collision)
		{
			i++;
			pBCollider = gpUnitManager->getBullet(i);

			if(pBCollider->isActive() == false) continue;

			else if(pBCollider->isDangerous() && pBCollider->checkDistanceCollision(mpPlayer))
			{
				pBCollider->disable();
				collision = true;
				gpEventSystem->fireEvent(TankDestroyedEvent());
				gpUnitManager->removeSpecific(mpPlayer->getMapName());
				mpPlayer = nullptr;
				gpEventSystem->fireEvent(LevelFailedEvent());
			}
		}

		//collisions with wall

	}
}
void Level::collisionsEnemies()
{
	for (int i = 0; i < NUM_TANKS; i++)
	{
		if(mpEnemyTanks[i] != nullptr)
		{
			//Unit* collider;
			Bullet* pBCollider;
			bool collision = false;

			int j = -1;
			while(gpUnitManager->getBullet(j + 1) && !collision)
			{
				j++;
				pBCollider = gpUnitManager->getBullet(j);

				if(pBCollider->isActive() == false) continue;

				else if(pBCollider->isDangerous() && pBCollider->checkDistanceCollision(mpEnemyTanks[i]))
				{
					pBCollider->disable();
					collision = true;
					gpEventSystem->fireEvent(TankDestroyedEvent());
					gpUnitManager->removeSpecific(mpEnemyTanks[i]->getMapName());
					mNumEnemies --;
					gpGame->addPoints(200);
					
					mpEnemyTanks[i] = nullptr;
				}
			}

			//collisions with wall
		}
	}

}
void Level::collisionsBullets()
{
	int i = -1;
	Bullet* pBullet;
	Bullet* pBCollider;
//	GridUnit* pWall;
	bool collision;
	while(gpUnitManager->getBullet(i + 1))
	{
		collision = false;
		i++;
		pBullet = gpUnitManager->getBullet(i);
		if(pBullet->isActive() == false) continue;
		else
		{
			//check bullet on bullet
			int j = i;
			while(gpUnitManager->getBullet(j + 1) && !collision)
			{
				j++;
				pBCollider = gpUnitManager->getBullet(j);

				if(pBCollider->isActive() == false) continue;

				else if(pBCollider->checkDistanceCollision(pBullet) && pBullet->isDangerous())
				{
					pBCollider->disable();
					pBullet->disable();
					collision = true;
				}
			}

			//check bullet wall;

		
			if(!collision)
			{
				int	bulletX =			(int)(pBullet->getLocation().getX() - pBullet->getCurrentSprite()->getWidth()/2),
						bulletY =		(int)(pBullet->getLocation().getY() - pBullet->getCurrentSprite()->getHeight()/2),
						bulletWidth =	(int)pBullet->getCurrentSprite()->getWidth(),
						bulletHeight =	(int)pBullet->getCurrentSprite()->getHeight(),
						wallWidth = 32, //=		pWall->getCurrentSprite()->getWidth(),
						wallHeight = 32; //=	pWall->getCurrentSprite()->getHeight();


				int length = mWallTileUnits.size();
				for (int k = 0; k < length; k++)
				{
					if(pBullet->checkDistanceCollisionWithWall(mWallTileUnits.at(k)))
					{
						handleCollisionBulletWall(pBullet, mWallTileUnits.at(k));
						collision = true;
					}
				}
				//if(collision) pBullet->bounced();
			}
			//if(collision)continue;
		}
	}

}

void Level::handleCollisionBulletWall(Bullet* bullet, GridUnit* wall)
{
	int	bulletX =		(int)(bullet->getLocation().getX() - bullet->getCurrentSprite()->getWidth()/2),
		bulletY =		(int)(bullet->getLocation().getY() - bullet->getCurrentSprite()->getHeight()/2),
		bulletWidth =	(int)bullet->getCurrentSprite()->getWidth(),
		bulletHeight =	(int)bullet->getCurrentSprite()->getHeight(),
		wallX = 		(int)wall->getLocation().getX(),
		wallY =			(int)wall->getLocation().getY(),
		wallWidth = 32,
		wallHeight = 32;




	// check above to see if tile exists and if it is a floor
	if(!(wallY - 1 < 0) && mGrid[wallX][wallY - 1] == 0 && bullet->bulletVelocity().getY() > 0)
	{
		//check if bulletbottom is below the wall top
		if(bulletY + bulletHeight > wallY * 32 && !(bulletY > wallY * 32))
		{
			bullet->bounceY();
		}
	}
	//check below to see if tile exists and if it is floor
	else if(!(wallY + 1 > GRID_HEIGHT) && mGrid[wallX][wallY + 1] == 0 && bullet->bulletVelocity().getY() < 0)
	{
		//check if bullet is above wall bottom
		if(bulletY < (wallY * 32 + wallHeight)  && !(bulletY + bulletHeight < (wallY * 32 + wallHeight)))
		{
			bullet->bounceY();
		}
	}
	//check left to see if tile exists and is floor

	if(!(wallX - 1 < 0) && mGrid[wallX - 1][wallY] == 0 && bullet->bulletVelocity().getX() > 0)
	{
		//check if bullet is inside of left side of wall
		if(bulletX + bulletWidth > wallX * 32 && !(bulletX > wallX * 32))
		{
			bullet->bounceX();
		}
	}
	//check right to see if tile exists and is floor
	else if(!(wallX + 1 > GRID_WIDTH) && mGrid[wallX + 1][wallY] == 0 && bullet->bulletVelocity().getX() < 0)
	{
		//check if bullet is inside of right side of wall
		if(bulletX  < (wallX * 32 + wallWidth) && !(bulletX + bulletWidth < (wallX  * 32 + wallWidth)))
		{
			bullet->bounceX();
			
		}
	}
}
void Level::saveLevel(std::ofstream& file)
{
	file << mLevelName <<endl;
	//player location
	file << (int)mpPlayer->getLocation().getX() / 32  + 1 << " " << (int)mpPlayer->getLocation().getY() / 32 + 1 << endl;
	//number of enemies
	file << (int)mNumEnemies << endl;

	//enemy locations
	for (int i = 0; i < NUM_TANKS; i++)
	{
		if(mpEnemyTanks[i] != NULL && mpEnemyTanks[i] != nullptr)
		{
			file << (int)mpEnemyTanks[i]->getLocation().getX()  / 32  + 1<< " " << (int)mpEnemyTanks[i]->getLocation().getY() / 32 + 1 << " "  << tankTypes[i] << endl;
		}
	}
	//levellayout

	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			file << mGrid[j][i] << " ";
		}

		file << endl;
	}

}

void Level::loadSave(std::ifstream& file, ResourceManager* pResourceManager)
{
	
	mpResources = pResourceManager;
	int x, y;

	//levelname
	getline(file, mLevelName);
	
	//player location
	file >> x;
	file >> y;
	mPlayerSpawn = Vector2D((float)x, (float)y);

	//number of enemies
	file >> storedNumTanks;
	mNumEnemies = storedNumTanks;


	//enemy locations
	for (int i = 0; i < storedNumTanks; i++)
	{
		file >> x;
		file >> y;
		file >> tankTypes[i];
		mEnemySpawn.push_back(Vector2D((float)x, (float)y));
	}
	//levellayout
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			file >> mGrid[j][i];
		}
	}


}


