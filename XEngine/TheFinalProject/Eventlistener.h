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
	EventListener(GameEventType t) 
	{
		switch (t)
		{
		case GameEventType::Death:
			audioFile = "Shoot1.wav";
			break;
		case GameEventType::Shoot:
			audioFile = "Shoot3.wav";
			break;
		case GameEventType::ShootS:
			audioFile = "Shoot4.wav";
		default:
			break;
		}
	}
	void HandleEvent()
	{
		X::SetAudioPath("../Data/Sounds");
		audioId = X::LoadAudio(audioFile);
		switch (mEventType)
		{
		case GameEventType::Shoot:
			X::PlayAudio(audioId, false, 1.0f, 1.0f, 1.0f);
			break;
		case GameEventType::ShootS:
			X::PlayAudio(audioId, false, 0.1f, 1.0f, 1.0f);
			break;
		case GameEventType::Death:
			X::PlayAudio(audioId, false, 0.2f, 1.0f, 1.0f);
			break;
		}
		
	}

private:
	GameEventType mEventType;
	int audioId = -1;
	const char* audioFile;

};
#endif // !EVENT_LISTENER_HEADER