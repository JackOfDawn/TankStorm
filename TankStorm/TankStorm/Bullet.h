#ifndef BULLET_H
#define BULLET_H

#include "Unit.h"

class Bullet : public Unit
{
public:
	Bullet(Animation* animation);
	~Bullet();
	
	virtual void draw(GraphicsBuffer* targetDrawBuffer);

	bool isDangerous();
	void disable();
	void spawnBullet(Vector2D location, double angle, float speedm, float accuracy = 0.0f, int bounces = 0);

	void bounceX();
	void bounceY();
	void bounced();

	Vector2D getNextLocation();

	virtual void update(float frameDelay);
	bool isActive();

	bool checkDistanceCollisionWithWall(Unit* pWall);
	
	Vector2D bulletVelocity();
	
private:
	bool		mIsActive;
	float		mSpeed;
	Vector2D	mVelocity;
	float		mCooldown;
	float		mBouncesLeft;

	void handleMovement();
	

	virtual void handleEvent(const Event& theEvent);
	virtual inline std::string getClassName( void ) const { return "Bullet "; }
};

#endif