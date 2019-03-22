//====================================================================================================
// Filename:	AudioObject.h
// Created by:	Craig Lacey
//====================================================================================================

#ifndef INCLUDED_XENGINE_AUDIOOBJECT_H
#define INCLUDED_XENGINE_AUDIOOBJECT_H

#include "XAudioTypes.h"
#include <fmod.h>

namespace X {

	class AudioSource
	{
	public:
		AudioSource();
		AudioSource(Audio::AudioEngineType type, FMOD::System* system = nullptr);
		~AudioSource();

		void Load(FMOD::System* pFMODSystem, const char* filename);
		void Clear();
		
		void Play(bool loop) const;
		void Play(bool loop, float vol, float pitch, float pan) const;

	private:
		Audio::AudioEngineType mType;
		FMOD::System* const mFMODSystem;
		FMOD::Sound* mFMODSound;
		FMOD::Channel* mFMODChannel;
	};

} // namespace X

#endif // #ifndef INCLUDED_XENGINE_AUDIOOBJECT_H
