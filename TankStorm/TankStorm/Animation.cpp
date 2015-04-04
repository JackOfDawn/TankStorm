/*
	Author:		Spencer Martin
	Assignment: #3
	Due Date:	1/28/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	These are the functions for the Animation class.
*/

#include "Animation.h"
#include <vector>



Animation::Animation(float speed, bool loopCheck)
{
	mSpeed = speed;
	mShouldLoop=loopCheck;

	mSpriteList = std::vector<Sprite*>();
}



Animation::Animation(vector<Sprite*> sprite, float speed, bool loopCheck)
{
	mSpeed = speed;
	mShouldLoop=loopCheck;

	mSpriteList = sprite;
}


Animation::~Animation()
{
	
}

void Animation::addSprite(Sprite* sprite)
{
	mSpriteList.push_back(sprite);
}

Sprite* Animation::getSpriteAt(int frame)
{
	if (frame >= 0 && frame < (int)mSpriteList.size())
	{
		return mSpriteList[frame];
	}

	return nullptr;
}

bool Animation::getShouldLoop()
{
	return mShouldLoop;
}



