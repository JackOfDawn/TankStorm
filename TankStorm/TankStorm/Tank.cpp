#include "Tank.h"
#include "TankMovement.h"
#include <math.h>

Tank::Tank(Vector2D location, Animation* animation, Sprite* barrel)
	:Unit(location, animation)
{
	mBarrelRotation = 0;
	mBodyRotation = 0;
	mpBarrel = barrel;
	movingBackwards = false;
	movingForward = false;
	mAccuracy = 0;	mTankMovement = nullptr;}

Tank::~Tank()
{
	delete mTankMovement;
	mTankMovement = nullptr;
}

void Tank::update(float framedelay)
{
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

	movingForward = false;
	movingBackwards = false;
	Unit::update((float)framedelay);
}

void Tank::drawOrigin(GraphicsBuffer* targetBuffer)
{
	targetBuffer->drawOrigin(mLocation, getCurrentSprite(), mBodyRotation);
	Vector2D offset(mLocation.getX(), mLocation.getY());
	targetBuffer->drawOrigin(offset, mpBarrel, mBarrelRotation);
}

void Tank::draw(GraphicsBuffer* targetBuffer)
{
	drawOrigin(targetBuffer);
}

void Tank::handleEvent( const Event& theEvent )
{

}