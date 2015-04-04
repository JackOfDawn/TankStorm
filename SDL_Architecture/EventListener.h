#pragma once

#include "Trackable.h"

class Event;

class EventListener:public TrackableObject
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent( const Event& theEvent ) = 0;

	virtual inline std::string getClassName( void ) const { return "Event Listener "; }

private:

};