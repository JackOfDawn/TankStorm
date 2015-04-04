#include "Bullet.h"
#include "MiscDataDef.h"
#include "Sprite.h"


Bullet::Bullet(Animation* animation)
	:Unit(Vector2D(), animation)
{
	mIsActive = false;
	mSpeed = 0.0f;
	mVelocity = Vector2D();
	mLocation = Vector2D( -100, -100);
	mType = UNIT_TYPES[BULLET];
}

Bullet::~Bullet()
{

}

void Bullet::spawnBullet(Vector2D location, double angle, float speed, float accuracy, int bounces)
{
	float acc = (((float)rand() / RAND_MAX) -.5f) * accuracy;
	mIsActive = true;
	mLocation = location;
	mVelocity = Vector2D(cos((float)angle + acc) * speed, sin((float)angle + acc) * speed);
	//cout << endl << mVelocity
	mSpeed = speed;
	mCooldown = 300;
	mBouncesLeft = (float)bounces; 
}

void Bullet::update(float frameDelay)
{
	if (mIsActive)
	{
		if(mBouncesLeft < 0)
		{
			disable();
		}
		else
		{
			if (mCooldown > 0)
			{
				mCooldown -=  frameDelay;
			}
			handleMovement();
		}

	}
	Unit::update(frameDelay);
}

void Bullet::draw(GraphicsBuffer* targetDrawBuffer)
{
	if(mIsActive)
		targetDrawBuffer->drawOrigin(mLocation, getCurrentSprite(), 0);
}

bool Bullet::isDangerous()
{
	if(mCooldown <= 0) return true;
	return false;
}

void Bullet::handleMovement()
{
	float newXLoc;
	float newYLoc;

	newXLoc = mLocation.getX() + mVelocity.getX();
	newYLoc = mLocation.getY() + mVelocity.getY();

	mLocation.setX(newXLoc);
	mLocation.setY(newYLoc);

	if(newXLoc < 0 || newXLoc > DISPLAY_WIDTH ||
		newYLoc < 0 || newYLoc > DISPLAY_HEIGHT)
	{
		disable();
	}
}

bool Bullet::isActive()
{
	
	return mIsActive;
}

void Bullet::handleEvent(const Event& theEvent)
{

}

void Bullet::disable()
{
	mIsActive = false;
}

void Bullet::bounceX()
{
	mVelocity.setX(mVelocity.getX() * (-1));
	//mBouncesLeft--;
}
void Bullet::bounceY()
{
	mVelocity.setY(mVelocity.getY() * (-1));
	//mBouncesLeft--;

}

Vector2D Bullet::getNextLocation()
{
	return Vector2D(mLocation.getX() + mVelocity.getX(), mLocation.getY() + mVelocity.getY());
}

bool Bullet::checkDistanceCollisionWithWall(Unit* pWall)
{
	
	float	wallMidX = pWall->getLocation().getX() + (pWall->getCurrentSprite()->getWidth()/2),
			wallMidY = pWall->getLocation().getY() + (pWall->getCurrentSprite()->getHeight()/2);

	float	dX = this->getNextLocation().getX() - wallMidX,
			dY = this->getNextLocation().getY() - wallMidY,
			distSq = (dX * dX) + (dY * dY),
			radiusThis = ((float)(this->getCurrentSprite()->getWidth() /2)),
			radiusThat = ((float)(pWall->getCurrentSprite()->getWidth() /2)),
			radiiSQ = (radiusThis * radiusThis) + (radiusThat * radiusThat);


	if(distSq <= radiiSQ) return true;
	return false;
}


Vector2D Bullet::bulletVelocity()
{
	return mVelocity;
}

void Bullet::bounced()
{
	mBouncesLeft--;
}