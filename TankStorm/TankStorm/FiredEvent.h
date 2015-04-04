#ifndef FIRED_EVENT_H
#define FIRED_EVENT_H

#include "Event.h"
#include "Vector2D.h"

class FiredEvent : public Event
{
public:
	FiredEvent(Vector2D location, double angle, float speed, float accuracy);
	~FiredEvent();

	Vector2D location;
	double angle;
	float speed;
	float accuracy;
};

#endif