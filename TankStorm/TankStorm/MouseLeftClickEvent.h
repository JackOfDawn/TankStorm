#ifndef MLC_H
#define MLC_H

#include "Event.h"

class MouseLeftClickEvent : public Event
{
public:
	MouseLeftClickEvent();
	~MouseLeftClickEvent();
};

#endif