#pragma once
#include "Tank.h"

class AITank : public Tank
{
public:
	AITank(Vector2D location, Animation* animation, Sprite* barrel, int movement);
	virtual ~AITank();
	void inline upShotFreq() {mShotFrequency+=500;}
	void inline cutShotFreq() {mShotFrequency-=500;}

	virtual void update(float frameDelay);
private:
	double mShotFrequency;
	double mShotCountdown;

	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "AITank "; }
};

