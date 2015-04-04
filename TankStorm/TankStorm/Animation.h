/*
	Author:		Spencer Martin
	Assignment: #3
	Due Date:	1/28/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	This is a the header for the Animation class that holds Sprite info.
*/

#pragma once

#include "Unit.h"
#include "Sprite.h"
#include "Vector2D.h"
#include <vector>

#include "Timer.h"
#include "Trackable.h"

using namespace std;

class Animation : public TrackableObject
{
private:
	std::vector<Sprite*> mSpriteList;

	bool	mShouldLoop;
	float	mSpeed;

public:
	Animation(std::vector<Sprite*> sprite, float speed, bool loopCheck);
	Animation(float speed, bool loopCheck);
	virtual ~Animation();

	inline std::vector<Sprite*> getSpriteList() const {return mSpriteList;}

	float getSpeed() const { return mSpeed; }
	void setSpeed(float val) { mSpeed = val; }

	void addSprite(Sprite* sprite);
	Sprite* getSpriteAt(int frame);
	bool getShouldLoop();

	virtual inline std::string getClassName( void ) const { return "Animation"; }

};