/*
	Author:		Spencer Martin
	Assignment: #3
	Due Date:	1/28/14

	Certificate of Authenticity: I certify that, with the exception of where noted, 
								 this project is my own work.

	Purpose:	This is a the header for the Unit class that holds state information.
*/

#pragma once

#include "Vector2D.h"
#include "GraphicsBuffer.h"

#include "EventListener.h"



class Animation;

typedef std::string type;

class Unit : public EventListener
{
protected:
	Vector2D mLocation;
	Animation* mpAnimation;
	type mType;
private:
	float mAnimationTimeout;
	int mAnimationFrame;
	
	std::string mName;
	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "Unit"; }

public:
	

	Unit(Vector2D location, Animation* animation);
	Unit();
	virtual ~Unit();

	virtual void update(float frameDelay);
	void adjustLocation(Vector2D newLocation);
	virtual void draw(GraphicsBuffer* targetDrawBuffer);
	virtual void drawOrigin(GraphicsBuffer* targetDrawBuffer);
	virtual void drawScaled(GraphicsBuffer* targetDrawBuffer, float scaleFactor);
	Animation* getAnimation(){return mpAnimation;}
	Vector2D getLocation(){return mLocation;}
	inline void changeAnimation(Animation* newAnimation) {mpAnimation = newAnimation; mAnimationFrame = 0;}

	inline type getType() {return mType;}
	
	bool checkDistanceCollision(Unit* pUnit);
	//bool checkDistanceCollisionWithWall(Unit* pUnit);

	Sprite* getCurrentSprite( void );

	inline std::string getMapName() {return mName;}
	inline void setMapName(std::string name) {mName = name;}
};