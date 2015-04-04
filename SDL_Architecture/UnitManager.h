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
#include "Unit.h"

using namespace std;

class GraphicsBuffer;
class ResourceManager;


class UnitManager : public TrackableObject
{
public:
	UnitManager(ResourceManager* pResourceManager);
	virtual ~UnitManager();

	void addUnit(const std::string &key, Unit* newUnit);
	void addUnit(Unit* newUnit);
	void deleteAll();
	void removeSpecific(std::string key);
	void removeSpecific(Unit* unit);
	void deleteUnitByMouse(int checkX, int checkY);
	void draw(GraphicsBuffer* targetBuffer);
	Unit* findUnit(const std::string &key);
	void switchPause();
	void update(float frameDelay);
	inline bool getPauseState() {return mPaused;};

	virtual inline string getClassName( void ) const { return "UnitManager "; }

private:
	map<std::string, Unit*> mUnitMap;
	bool mPaused;
	ResourceManager* mpResourceManager;


};


extern UnitManager* gpUnitManager;
