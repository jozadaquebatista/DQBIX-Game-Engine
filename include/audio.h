#ifndef __IX_AUDIOCLIP__
#define __IX_AUDIOCLIP__
#pragma once

#include <string>
#include "audio_backend.h"
#include "lua.hpp"
#include "component.h"

class AudioClip : public Component
{
public:
    AudioClip(std::string filename = "");
    AudioClip(unsigned char* data = 0);
        AudioClip(const AudioClip&) {}
    void operator=(AudioClip other) {}

    virtual ~AudioClip();

	void play();
	void pause();
	void stop();

	float volume, pitch, pan;
	bool loop, play_once, playing;

    inline static void RegisterObject(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
            .beginClass<AudioClip>("AudioClip")
			.addConstructor<void(*)(std::string)>()
            .addFunction("play", &AudioClip::play)
            .addFunction("pause", &AudioClip::pause)
            .addFunction("stop", &AudioClip::stop)
            .addData("volume", &AudioClip::volume)
            .addData("pitch", &AudioClip::pitch)
            .addData("pan", &AudioClip::pan)
            .addData("loop", &AudioClip::loop)
            .addData("playonce", &AudioClip::play_once)
            .addData("playing", &AudioClip::playing, false)
			.endClass();
	}
private:
	bool oshot;
	HSTREAM hm;
};

#endif //__IX_AUDIOCLIP__
