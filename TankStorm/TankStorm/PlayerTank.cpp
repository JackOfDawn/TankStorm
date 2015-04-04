#include "PlayerTank.h"
#include "Event.h"
#include "EventSystem.h"
#include "MouseMoveEvent.h"
#include "FiredEvent.h"
#include "TankMovement.h"
#include "MiscDataDef.h"
#include "Game.h"

PlayerTank::PlayerTank(Vector2D location, Animation* animation, Sprite* barrel)
	: Tank(location, animation, barrel)
{
	mSpeed = 1.5;
	gpEventSystem->addListener(UP_ARROW_EVENT, this);
	gpEventSystem->addListener(RIGHT_ARROW_EVENT, this);
	gpEventSystem->addListener(LEFT_ARROW_EVENT, this);
	gpEventSystem->addListener(DOWN_ARROW_EVENT, this);
	gpEventSystem->addListener(MOUSE_MOVED_EVENT, this);
	gpEventSystem->addListener(MOUSE_LEFT_CLICK_EVENT, this);
	mBodyRotation = 0;

	mTankMovement = New PlayerMovement();
	mType = UNIT_TYPES[PLAYER];
	mAccuracy = .3;
}

PlayerTank::~PlayerTank()
{
	
}

void PlayerTank::update(float framedelay)
{
	mBarrelRotation = -(180.0f/M_PI) * (atan2(mAimLocation.getY() - mLocation.getY(), mAimLocation.getX() - mLocation.getX()));
	Tank::update(framedelay);

	//gpEventSystem->fireEvent(FiredEvent(mLocation, mBarrelRotation * -(M_PI/180), 3, .2));
}


void PlayerTank::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == UP_ARROW_EVENT)
	{
		movingForward = true;
		movingBackwards = false;

	}
	else if (theEvent.getType() == DOWN_ARROW_EVENT)
	{
		movingForward = false;
		movingBackwards = true;
	}

	if(theEvent.getType() == LEFT_ARROW_EVENT)
	{
		mBodyRotation += 3;

	}
	else if (theEvent.getType() == RIGHT_ARROW_EVENT)
	{
		mBodyRotation -= 3;
	}

	if(theEvent.getType() == MOUSE_MOVED_EVENT)
	{
		const MouseMovedEvent& moveEvent = static_cast<const MouseMovedEvent&>(theEvent);
		mAimLocation.setX((float)moveEvent.x);
		mAimLocation.setY((float)moveEvent.y);
	}

	if(theEvent.getType() == MOUSE_LEFT_CLICK_EVENT)
	{
		//cout << "\n" << mBarrelRotation << "\n" << mBarrelRotation * (M_PI/180);
		//gpEventSystem->fireEvent(FiredEvent(mLocation, (float)(mBarrelRotation * -(M_PI/180)), 3, .4f));
		gpEventSystem->fireEvent(FiredEvent(mLocation, mBarrelRotation * -(M_PI/180.0), 3, mAccuracy));
		gpGame->addPoints(-20);
	}


} 