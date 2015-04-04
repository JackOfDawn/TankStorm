/*	Author:		Spencer Martin
 *	Class:		EGP 310-02
 *	Assignment:	Midterm, Snake
 *	File:		ModEvent.h
 *	Certificate of Authenticity:	I certify that this project is entirely my own work.
 *****************************************************************************************/

#pragma once
#include "Event.h"

class SpeedUpEvent : public Event
{
public:
	SpeedUpEvent();
	~SpeedUpEvent();


private:

};

class SlowDownEvent : public Event
{
public:
	SlowDownEvent();
	~SlowDownEvent();

private:

};