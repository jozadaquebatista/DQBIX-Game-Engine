#ifndef __STOPWATCH__
#define __STOPWATCH__

#pragma once
#include "lua.hpp"

class Stopwatch
{
public:
	Stopwatch();

	void Start();
	void Restart();
	void Reset();
	void Stop();
	int ElapsedMillis();
	
	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<Stopwatch>("clock")
			.addConstructor<void(*)(void)>()
			.addFunction("start", &Stopwatch::Start)
			.addFunction("restart", &Stopwatch::Restart)
			.addFunction("reset", &Stopwatch::Reset)
			.addFunction("stop", &Stopwatch::Stop)
			.addFunction("elapsed", &Stopwatch::ElapsedMillis)
			.endClass();
	}

private:
	int s_ticks;
	bool isRunning;
};

Stopwatch::Stopwatch()
{
	isRunning = false;
	Reset();
}

void Stopwatch::Start()
{
	if (!isRunning)
	{
		s_ticks = SDL_GetTicks();
		isRunning = true;
	}
}

void Stopwatch::Stop()
{
	if (isRunning)
	{
		s_ticks = 0;
		isRunning = false;
	}
}

void Stopwatch::Reset()
{
	isRunning = false;
	s_ticks = 0;
}

void Stopwatch::Restart()
{
	isRunning = true;
	s_ticks = SDL_GetTicks();
}

int Stopwatch::ElapsedMillis()
{
	if (isRunning)
	{
		return SDL_GetTicks() - s_ticks;
	}
	return 0;
}

#endif //__STOPWATCH__