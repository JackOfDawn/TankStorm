#ifndef TANK_MOVEMENT
#define TANK_MOVEMENT

#include "Trackable.h"

class TankMovement : public TrackableObject
{
public:
	TankMovement();
	virtual ~TankMovement();
	inline int const getMoveType() {return MoveType;}

	virtual inline std::string getClassName( void ) const { return "TankMovement "; }

protected:
	virtual void movement();
	int MoveType;

private:



};

#endif

#ifndef PLAYER_MOVEMENT
#define PLAYER_MOVEMENT

class PlayerMovement : public TankMovement
{
public:
	PlayerMovement();
	virtual ~PlayerMovement();

};


#endif

#ifndef STATIONARY
#define STATIONARY

class Stationary : public TankMovement
{
public:
	Stationary();
	virtual ~Stationary();

};



#endif

#ifndef HORIZONTAL_PATROL
#define HORIZONTAL_PATROL

class HorizontalPatrol : public TankMovement
{
public:
	HorizontalPatrol();
	virtual ~HorizontalPatrol();


};


#endif