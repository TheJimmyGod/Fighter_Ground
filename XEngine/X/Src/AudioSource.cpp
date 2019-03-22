//====================================================================================================
// Filename:	AudioSource.cpp
// Created by:	Craig Lacey
//====================================================================================================

#include "Precompiled.h"
#include "AudioManager.h"
#include "AudioSource.h"

using namespace X;

AudioSource::AudioSource()
	:mFMODSystem(nullptr)
{
	mType = Audio::AudioEngineType::UNKNOWN;	
	mFMODSound = nullptr;
	mFMODChannel = 0;
}

//----------------------------------------------------------------------------------------------------

AudioSource::AudioSource(Audio::AudioEngineType type, FMOD::System* fmodSystem)
	:mFMODSystem(fmodSystem)
{
	mType = type;
	mFMODSound = nullptr;
	mFMODChannel = 0;
}

//----------------------------------------------------------------------------------------------------

AudioSource::~AudioSource()
{
	if (mFMODSound)
	{
		mFMODSound->release();
	}
	if (mFMODChannel)
	{
		delete mFMODChannel;
		mFMODChannel = nullptr;
	}
	// DO NOT DELETE THE FMOD SYSTEM !!!
}

//----------------------------------------------------------------------------------------------------

void AudioSource::Load(FMOD::System* pFMODSystem, const char* filename)
{
	if (FMOD_OK != pFMODSystem->createSound(filename, FMOD_DEFAULT, 0, &mFMODSound))
	{
		XLOG("[AudioSource] Error Loading Sound File -- Could not create fmod sound from file: %s", filename);
		return;
	}
}

//----------------------------------------------------------------------------------------------------

void AudioSource::Clear()
{
	if (mFMODSound)
	{
		mFMODSound->release();
	}
}

//----------------------------------------------------------------------------------------------------

void AudioSource::Play(bool loop) const
{
	switch (mType)
	{
	case Audio::AudioEngineType::DIRECTX:
		// DirectX Removed.
		break;
	case Audio::AudioEngineType::FMOD:
		if (loop)
		{
			mFMODSound->setMode(FMOD_LOOP_NORMAL);
			FMOD::Channel* pChannel = 0; // FIXME - can't use &mFMODChannel because of default const qualifier
			mFMODSystem->playSound(mFMODSound, 0, false, &pChannel);
		}
		else
		{
			mFMODSound->setMode(FMOD_LOOP_OFF);
			FMOD::Channel* pChannel = 0; // FIXME - can't use &mFMODChannel because of default const qualifier
			mFMODSystem->playSound(mFMODSound, 0, false, &pChannel);
		}
		break;
	default:
		XLOG("[AudioSource] Could not play audio because engine type is unhandled");
		break;
	}
}

//----------------------------------------------------------------------------------------------------