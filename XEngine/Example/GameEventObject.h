#ifndef GAME_EVENT_OBJECT_HEADER_H_
#define GAME_EVENT_OBJECT_HEADER_H_

#include "SimpleEvent.h"
#include "XEngine.h"

using namespace SimpleEvent;
using namespace X;

class GameEventObject : Object
{
public:
	Event mEvent;
	void MessageLoop(short param) override
	{
		switch (param)
		{
		case 4:
			XLOG("Event 4 Detected");
			break;
		default:
			XLOG("GameEventObject param %d received", param);
			break;
		}
	}

};



#endif // !GAME_EVENT_OBJECT_HEADER_H_
