#ifndef __IX_AUDIO__
#define __IX_AUDIO__
#pragma once

#include <string>
#include "audio_backend.h"

#include "lua.hpp"
class audio
{
public:
	audio(std::string filename = "");
        audio(const audio&) {}
	void operator=(audio other) {}

	virtual ~audio();

	void play();
	void pause();
	void stop();

	float volume, pitch, pan;
	bool loop, play_once, playing;

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<audio>("sound")
			.addConstructor<void(*)(std::string)>()
			.addFunction("play", &audio::play)
			.addFunction("pause", &audio::pause)
			.addFunction("stop", &audio::stop)
			.addData("volume", &audio::volume)
			.addData("pitch", &audio::pitch)
			.addData("pan", &audio::pan)
			.addData("loop", &audio::loop)
			.addData("playonce", &audio::play_once)
			.addData("playing", &audio::playing, false)
			.endClass();
	}
private:
	bool oshot;
	HSTREAM hm;
};

#endif //__IX_AUDIO__
