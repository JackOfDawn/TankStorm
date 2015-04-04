#pragma once

#include <string>
#include "Trackable.h"

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	UP_ARROW_EVENT,
	DOWN_ARROW_EVENT,
	LEFT_ARROW_EVENT, 
	RIGHT_ARROW_EVENT,
	SPACE_BAR_EVENT,
	ESC_KEY_EVENT,
	LEVEL_COMPLETE_EVENT,
	LEVEL_FAILED_EVENT,
	SPEED_SNAKE_EVENT,
	SLOW_SNAKE_EVENT,
	GAME_COMPLETE_EVENT,
	ADD_POINTS_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =	{	"Up Event",
												"Down Event",
												"Left Event",
												"Right Event",
												"Space Bar Event",
												"Escape Event",
												"Level Complete Event",
												"Level Failed Event",
												"Speed Snake Event", 
												"Slow Snake Event", 
												"Game Complete Event",
												"Add Points Event"
											};

class Event:public TrackableObject
{
public:
	Event( EventType type );
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

	virtual inline string getClassName( void ) const { return "Event"; }

private:
	EventType mType;

};