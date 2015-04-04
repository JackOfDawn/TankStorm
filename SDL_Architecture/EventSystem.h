#pragma once

#include <map>
#include "Trackable.h"

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem:public TrackableObject
{
public:
	EventSystem();
	virtual ~EventSystem();

	void fireEvent( const Event& theEvent );
	void addListener( EventType type, EventListener* pListener );
	void removeListener( EventType type, EventListener* pListener );
	void removeListenerFromAllEvents( EventListener* pListener );

	virtual inline string getClassName( void ) const { return "Event System "; }

private:
	static EventSystem* msInstance;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents( const Event& theEvent );

};

extern EventSystem* gpEventSystem;