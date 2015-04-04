#ifndef PLAYER_TANK
#define PLAYER_TANK

#include "Tank.h"

class PlayerTank : public Tank
{
public:
	PlayerTank(Vector2D location, Animation* animation, Sprite* barrel);
	virtual ~PlayerTank();

	virtual void update(float frameDelay);
private:

	virtual void handleEvent( const Event& theEvent );
	virtual inline std::string getClassName( void ) const { return "PlayerTank "; }
};

#endif