#include "AITank.h"
#include "MiscDataDef.h"
#include "Event.h"
#include "TankMovement.h"
#include "UnitManager.h"
#include "EventSystem.h"
#include "FiredEvent.h"
#include "Game.h"

AITank::AITank(Vector2D location, Animation* animation, Sprite* barrel, int movement)
	:Tank(location, animation, barrel)
{
	mSpeed = 0;
	mBodyRotation = 0;
	mShotCountdown = 0;
	int diff = gpGame->getDiffLevel();
	mType = UNIT_TYPES[ENEMY]; //"ENEMY";
	switch(movement)
	{
	case 1:
		cout << "What. Why?\n";
		break;
	case 2:
		mTankMovement = New Stationary();
		cout << "Stationary made.\n";
		if (diff == 1)
		{
			mShotFrequency = 3000;
		}
		else if (diff == 2)
		{
			mShotFrequency = 2000;
		}
		else
		{
			mShotFrequency = 1000;
		}
		break;
	case 3:
		mTankMovement = New HorizontalPatrol();
		cout << "Horizontal patroller.\n";
		mSpeed = 1;
		movingForward = true;
		if (diff == 1)
		{
			mShotFrequency = 4000;
		}
		else if (diff == 2)
		{
			mShotFrequency = 2500;
		}
		else
		{
			mShotFrequency = 1500;
		}
		break;
	}
}

AITank::~AITank()
{
	
}

void AITank::update(float framedelay)
{
	switch(mTankMovement->getMoveType())
	{
	case 1:
		cout << "Why does an AI tank have the player movement?\n";
		break;
	case 2:
		mShotCountdown += framedelay;
		if(mShotCountdown >= mShotFrequency)
		{
			gpEventSystem->fireEvent(FiredEvent(mLocation, mBarrelRotation * -(M_PI/180), 3, mAccuracy));
			mShotCountdown = 0;
		}
		break;
	case 3:
		//direction swap
		if(mLocation.getX() <= 48)
		{
			movingForward = true;
			movingBackwards = false;
		}
		if(mLocation.getX() >= 751)
		{
			movingForward = false;
			movingBackwards = true;
		}

		//movement management
		if(movingForward)
		{
			mLocation.setX((float)(mLocation.getX() + (mSpeed * cos((float)mBodyRotation * M_PI/180))));
			mLocation.setY((float)(mLocation.getY() - (mSpeed * sin((float)mBodyRotation * M_PI/180))));
		}
		if(movingBackwards)
		{
			mLocation.setX((float)(mLocation.getX() - (mSpeed * cos((float)mBodyRotation * M_PI/180))));
			mLocation.setY((float)(mLocation.getY() + (mSpeed * sin((float)mBodyRotation * M_PI/180))));
		}

		mShotCountdown += framedelay;
		if(mShotCountdown >= mShotFrequency)
		{
			gpEventSystem->fireEvent(FiredEvent(mLocation, mBarrelRotation * -(M_PI/180), 3, mAccuracy));
			mShotCountdown = 0;
		}
		break;
	}

	Vector2D playerLocation;
	if(gpUnitManager->findUnit("zPLAYER"))
		playerLocation = gpUnitManager->findUnit("zPLAYER")->getLocation();

	mBarrelRotation = -(180/M_PI) * (atan2(playerLocation.getY() - mLocation.getY(), playerLocation.getX() - mLocation.getX()));
	Unit::update((float)framedelay);
}

void AITank::handleEvent( const Event& theEvent )
{

}