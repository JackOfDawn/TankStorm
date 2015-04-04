#include "MouseMoveEvent.h"

MouseMovedEvent::MouseMovedEvent(int xx, int yy)
	:Event(MOUSE_MOVED_EVENT)
{
	x = xx;
	y = yy;
}

MouseMovedEvent::~MouseMovedEvent()
{

}