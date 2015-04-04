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
	ENTER_PRESSED_EVENT,
	ESC_KEY_EVENT,
	ACTIVATE_SE_EVENT,
	DEACTIVATE_SE_EVENT,
	VOLUME_INCREASE_EVENT,
	VOLUME_DECREASE_EVENT,
	DIFFICULTY_INCREASE_EVENT,
	DIFFICULTY_DECREASE_EVENT,
	LEVEL_COMPLETE_EVENT,
	LEVEL_FAILED_EVENT,
	TANK_DESTROYED_EVENT,
	TOGGLE_MUSIC_EVENT,
	TOGGLE_OPTIONS_EVENT,
	GAME_COMPLETE_EVENT,
	LOAD_GAME_EVENT,
	SAVE_GAME_EVENT,
	ADD_POINTS_EVENT,
	MOUSE_MOVED_EVENT,
	MOUSE_LEFT_CLICK_EVENT,
	FIRED_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[NUM_EVENT_TYPES] =	{	"Up Event",
												"Down Event",
												"Left Event",
												"Right Event",
												"Space Bar Event",
												"Enter Pressed Event",
												"Escape Event",
												"Activate Sound Effects Event",
												"Deactivate Sound Effects Event",
												"Volume Increase Event",
												"Volume Decrease Event",
												"Difficulty Increase Event",
												"Difficulty Decrease Event",
												"Level Complete Event",
												"Level Failed Event",
												"Tank Destroyed Event",
												"Toggle Music Event",
												"Toggle Options Event",
												"Game Complete Event",
												"Load Game Event",
												"Save Game Event",
												"Mouse Moved Event",
												"Mouse Left Click Event",
												"Fired Event",
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