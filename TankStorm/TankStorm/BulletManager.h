#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

class ResourceManager;
class UnitManager;

#include <vector>
#include "Vector2D.h"
#include "Bullet.h"

class BulletManager : public EventListener
{
public:
	BulletManager(ResourceManager* pResourceManager, UnitManager* pUnitManager);
	~BulletManager();

	void loadBullets();
	Bullet* getBullet(int i);


private:

	static const int NUM_BULLETS = 50;

	Bullet*				mpBullets[NUM_BULLETS];
	ResourceManager*	mpResourceManager;
	UnitManager*		mpUnitManager;
	
	
	
	void spawnBullet(Vector2D location, double angle, float speed, float accuracy);

	virtual void handleEvent (const Event& theEvent);
	virtual inline std::string getClassName( void ) const {return "BulletManager ";}



};



#endif  