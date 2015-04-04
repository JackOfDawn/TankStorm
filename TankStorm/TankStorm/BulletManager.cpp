#include "BulletManager.h"
#include "UnitManager.h"
#include "ResourceManager.h"
#include <sstream>
#include "FiredEvent.h"
#include "EventSystem.h"


BulletManager::BulletManager(ResourceManager* pResourceManager, UnitManager* pUnitManager)
{
	mpResourceManager = pResourceManager;
	mpUnitManager = pUnitManager;
	gpEventSystem->addListener(FIRED_EVENT, this);
}

BulletManager::~BulletManager()
{

}

void BulletManager::loadBullets()
{
	std::stringstream ss;
	Bullet* tmpBullet;
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		ss << "zzBULLET" << i;
		tmpBullet =  new Bullet(mpResourceManager->getAnimation("BULLET"));
		mpUnitManager->addUnit(ss.str(),tmpBullet);
		//push to vector
		mpBullets[i] = tmpBullet;

		ss.str("");
	}
}

void BulletManager::spawnBullet(Vector2D location, double angle, float speed, float accuracy)
{
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		if(mpBullets[i]->isActive() == false)
		{
			mpBullets[i]->spawnBullet(location, angle, speed, accuracy);
			break;
		}
	}
}

void BulletManager::handleEvent(const Event& theEvent)
{
	if(theEvent.getType() == FIRED_EVENT)
	{
		const FiredEvent& fireEvent = static_cast<const FiredEvent&>(theEvent);
		spawnBullet(fireEvent.location, fireEvent.angle, fireEvent.speed, fireEvent.accuracy);
	}
}

Bullet* BulletManager::getBullet(int i)
{
	if(i >= NUM_BULLETS)
		return nullptr;
	else
		return mpBullets[i];

}