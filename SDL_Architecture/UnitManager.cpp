/*
	Author:		Spencer Martin
	Assignment: #4
	Due Date:	2/7/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	These are the function definitions for UnitManager.
*/


#include "UnitManager.h"
#include "ResourceManager.h"
#include "Animation.h"
#include <sstream>

using namespace std;

UnitManager::UnitManager(ResourceManager* pResourceManager)
{
	mpResourceManager = pResourceManager;
	mPaused = false;
}

UnitManager::~UnitManager()
{
	deleteAll();
}

void UnitManager::addUnit(const string &key, Unit* newUnit)
{
	mUnitMap.insert(pair<string, Unit*>(key, newUnit));
}

void UnitManager::addUnit(Unit* newUnit)
{
	string key = "0";
	stringstream ss;
	int i = 0;
	while (mUnitMap.find(key) != mUnitMap.end())
	{
		++i;
		ss.clear(); ss.str(string()); // clear it
		ss << i;
		key = ss.str();
	}
	mUnitMap.insert(pair<string, Unit*>(key, newUnit));
}


void UnitManager::deleteAll()
{
	std::map<string, Unit*>::iterator it;
	for(it=mUnitMap.begin(); it!=mUnitMap.end();)
	{
		delete it->second;
		mUnitMap.erase(it);
		it=mUnitMap.begin();
	}
	mUnitMap.clear();	//more for good measure than anything else
}


void UnitManager::deleteUnitByMouse(int checkX, int checkY)
{
	int unitX;
	int unitY; 
	int unitW;
	int unitH;

	for(auto it=mUnitMap.begin(); it!=mUnitMap.end();)
	{
		Unit* pUnit = it->second;

		unitX = pUnit->getLocation().getX();
		unitY = pUnit->getLocation().getY();

		Sprite* pCurrSprite = pUnit->getCurrentSprite();

		if (pCurrSprite != nullptr)
		{
			unitW = pUnit->getCurrentSprite()->getWidth();
			unitH = pUnit->getCurrentSprite()->getHeight();
		}

		if(checkX >= unitX && checkX <= unitX + unitW &&
		   checkY >= unitY && checkY <= unitY + unitH)		   
		{
			delete pUnit;
			it = mUnitMap.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void UnitManager::draw(GraphicsBuffer* targetBuffer)
{
	if(!mPaused)
	{
		std::map<string, Unit*>::iterator it;

		for(it=mUnitMap.begin(); it!=mUnitMap.end(); ++it)
		{
			it->second->draw(targetBuffer);
		}
	}
}


Unit* UnitManager::findUnit(const string &key)
{
	return mUnitMap.find(key)->second;
}


void UnitManager::switchPause()
{
	if(mPaused == true)
		mPaused=false;
	else
		mPaused=true;
}

void UnitManager::update(float frameDelay)
{
	for(auto it=mUnitMap.begin(); it!=mUnitMap.end(); ++it)
	{
		it->second->update(frameDelay); //Timing will need to be fixed for this
	}

}

void UnitManager::removeSpecific( std::string key )
{
	auto it = mUnitMap.find(key);
	mUnitMap.erase(it);
}

void UnitManager::removeSpecific( Unit* unit )
{
	for(auto it=mUnitMap.begin(); it!=mUnitMap.end(); ++it)
	{
		if(it->second == unit)
		{
			mUnitMap.erase(it);
			break;
		}
	}
}
