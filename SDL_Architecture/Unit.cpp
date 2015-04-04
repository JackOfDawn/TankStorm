/*
	Author:		Spencer Martin
	Assignment: #3
	Due Date:	1/28/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	These are the functions for the Unit class.
*/


#include "Unit.h"
#include "GraphicsBuffer.h"
#include "Animation.h"


Unit::Unit(Vector2D location, Animation* animation)
{
	mLocation=location;
	mpAnimation=animation;
	mAnimationFrame = 0;

	if (mpAnimation != nullptr)
	{
		mAnimationTimeout = mpAnimation->getSpeed();
	}
}

Unit::Unit()
{
	mLocation = Vector2D(0,0);
	mAnimationTimeout = 0;
	mAnimationFrame = 0;
}

Unit::~Unit()
{

}

void Unit::update(float frameDelay)
{
	if(mpAnimation->getShouldLoop())
	{
		mAnimationTimeout -= frameDelay;
	
		if (mAnimationTimeout <= 0) // Time for the next frame
		{
			mAnimationTimeout = mpAnimation->getSpeed();
			mAnimationFrame++;

			if (unsigned(mAnimationFrame) >= mpAnimation->getSpriteList().size())
			{
				mAnimationFrame = 0;
			}
		}
	}
}

void Unit::draw(GraphicsBuffer* targetDrawBuffer)
{
	Sprite* pSprite = getCurrentSprite();
	if (pSprite)
		targetDrawBuffer->draw(mLocation, getCurrentSprite());
}

void Unit::drawOrigin(GraphicsBuffer* targetDrawBuffer)
{
	targetDrawBuffer->drawOrigin(mLocation, getCurrentSprite());
}

void Unit::drawScaled(GraphicsBuffer* targetDrawBuffer, float scaleFactor)
{
	targetDrawBuffer->drawScaled(mLocation, getCurrentSprite(), scaleFactor);
}

void Unit::adjustLocation(Vector2D newLocation)
{
	mLocation = newLocation;
}

Sprite* Unit::getCurrentSprite(void)
{
	return mpAnimation->getSpriteAt(mAnimationFrame);
}

void Unit::handleEvent(const Event& theEvent)
{

}

