#ifndef _NIX_STOPWATCH__
#define _NIX_STOPWATCH__
#pragma once

#include "sdl_backend.h"
class Stopwatch
{

public:
	Stopwatch();

	void Start();
	void Restart();
	void Reset();
	void Stop();
	int ElapsedMillis();
	
private:
	int s_ticks;
	bool isRunning;
	
};

#endif //__STOPWATCH__
