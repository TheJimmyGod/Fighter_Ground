#ifndef AUDIO_EVENT_OBJECT_HEADER_H_
#define AUDIO_EVENT_OBJECT_HEADER_H_

#include "SimpleEvent.h"
using namespace SimpleEvent;

#include "XEngine.h"
using namespace X;

class AudioEventObject : public Object
{
public:
	Event mEvent;
	void MessageLoop(short param) override
	{		
		X::PlayAudio(param, false, 0.1f, 1.0f, 0.5f);
	}
};

#endif // !AUDIO_EVENT_OBJECT_HEADER_H_

