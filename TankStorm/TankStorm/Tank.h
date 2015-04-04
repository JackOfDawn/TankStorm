#ifndef TANK_H
#define TANK_H

#include "Unit.h"

class TankMovement;

class Tank : public Unit
{
public:
	Tank(Vector2D location, Animation* animation, Sprite* barrel);
	virtual ~Tank();

	virtual void update(float framedelay);
	void draw(GraphicsBuffer* targetDrawBuffer);
	void drawOrigin(GraphicsBuffer* targetDrawBuffer);

	//inline void setAccuracy();

private:
	Tank();
	Sprite*		mpBarrel;
	//const int	OFFSET = 5;
protected:
	bool		movingForward;
	bool		movingBackwards;
	double		mBarrelRotation;
	double		mBodyRotation;
	float			mSpeed;
	float		mAccuracy; // Should be 0 <= X < 1 for best results, the closer to 1 you are, the less accurate

	TankMovement*	mTankMovement;

	Vector2D	mAimLocation;

	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "Tank "; }
};

#endif