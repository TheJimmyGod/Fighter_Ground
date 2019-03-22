#ifndef EVENT_LISTENER_HEADER
#define EVENT_LISTENER_HEADER

#include <iostream>
#include "XEngine.h"
using std::cout;
using std::endl;

#include "GameEventType.h"

class EventListener
{
public:
	EventListener() {}
	EventListener(GameEventType t) {}
	void HandleEvent()
	{
		int audioId = -1;
		const char* audioFile = "Fire.wav";
		X::SetAudioPath("../Data/Sounds");
		audioId = X::LoadAudio(audioFile);
		X::PlayAudio(audioId, false, 1.0f, 1.0f, 1.0f);
	}

private:
	GameEventType mEventType;

};

#endif // !EVENT_LISTENER_HEADER