/*
	Author:		Spencer Martin
	Assignment: #4
	Due Date:	2/7/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	This is a the header for the UnitManager that keeps track of the system's Units.
*/

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "Unit.h"
#include "PlayerTank.h"
#include "Bullet.h"
#include "AITank.h"


using namespace std;

class GraphicsBuffer;
class ResourceManager;
class BulletManager;


class UnitManager : public TrackableObject
{
public:
	UnitManager(ResourceManager* pResourceManager);
	virtual ~UnitManager();

	void addUnit(const std::string &key, Unit* newUnit);
	void addUnit(Unit* newUnit);
	void deleteAll();
	bool removeSpecific(std::string key);
	bool removeSpecific(Unit* unit);
	void deleteUnitByMouse(int checkX, int checkY);
	void draw(GraphicsBuffer* targetBuffer);
	Unit* findUnit(const std::string &key);
	void switchPause();
	void update(float frameDelay);
	inline bool getPauseState() {return mPaused;};
	void loadBullets();

	vector<Unit*>* checkCollisions(Unit* pUnit);

	virtual inline string getClassName( void ) const { return "UnitManager "; }

	Bullet* getBullet(int i);

private:
	map<std::string, Unit*> mUnitMap;
	bool mPaused;


	ResourceManager* mpResourceManager;
	BulletManager* mpBulletManager;

	

};


extern UnitManager* gpUnitManager;
