#include "TankMovement.h"

TankMovement::TankMovement()
{


}

TankMovement::~TankMovement()
{


}


void TankMovement::movement()
{
}


PlayerMovement::PlayerMovement()
{
	MoveType = 1;
}

PlayerMovement::~PlayerMovement()
{

}

Stationary::Stationary()
{
	MoveType = 2;
}

Stationary::~Stationary()
{

}

HorizontalPatrol::HorizontalPatrol()
{
	MoveType = 3;
}

HorizontalPatrol::~HorizontalPatrol()
{

}