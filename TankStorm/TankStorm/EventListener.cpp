#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	if( gpEventSystem != nullptr )
	{
		gpEventSystem->removeListenerFromAllEvents( this );
	}
}
