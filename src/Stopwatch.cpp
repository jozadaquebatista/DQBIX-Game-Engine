#include "../include/Stopwatch.h"

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
