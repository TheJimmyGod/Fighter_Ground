#include <XEngine.h>
#include "SimpleEvent.h"
#include "AudioEventObject.h"
#include "GameEventObject.h"
#include "VFXEventObject.h"

// Gloabals ... are bad mmmmkay.
int sfx_explosion_id;
const char* sfx_explosion = "Explosion.wav";
const char* audiopath = "../Data/Sounds";

int animation[8];
float animationTime = 1.0f;

GameEventObject* pGameEventDispatcher;
AudioEventObject* pAudioEventListener;
VFXEventObject* pVFXObj;

void Initialize();
void Cleanup();

float animTimeCounter = 0;
bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ZERO))
	{
		pGameEventDispatcher->mEvent(0);
	}
	else if (X::IsKeyPressed(X::Keys::FOUR))
	{
		pGameEventDispatcher->mEvent(4);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("Blank Slate", hInstance, 800, 600, 0);

	Initialize();

	X::Run(GameLoop);

	Cleanup();

	X::Stop();

	return 0;
}

void Initialize()
{
	X::SetAudioPath(audiopath);
	sfx_explosion_id = X::LoadAudio(sfx_explosion);

	pGameEventDispatcher = new GameEventObject();
	pAudioEventListener = new AudioEventObject();
	pVFXObj = new VFXEventObject();

	pAudioEventListener->Register(pGameEventDispatcher->mEvent, &AudioEventObject::MessageLoop);
	pVFXObj->Register(pGameEventDispatcher->mEvent, &VFXEventObject::MessageLoop);
}

void Cleanup()
{
	if (pGameEventDispatcher)
	{
		delete pGameEventDispatcher;
		pGameEventDispatcher = nullptr;
	}
	
	if (pAudioEventListener)
	{
		delete pAudioEventListener;
		pAudioEventListener = nullptr;
	}
}