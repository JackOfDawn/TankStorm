#pragma once
#include "Event.h"

class MouseMovedEvent :public Event
{
public:
	MouseMovedEvent(int xx, int yy);
	~MouseMovedEvent();

	int x;
	int y;
private:

};