#include "FiredEvent.h"

FiredEvent::FiredEvent(Vector2D location, double angle, float speed, float accuracy)
	:Event(FIRED_EVENT)
{
	this->location = location;
	this->angle = angle;
	this->speed = speed;
	this->accuracy = accuracy;
}

FiredEvent::~FiredEvent()
{

}