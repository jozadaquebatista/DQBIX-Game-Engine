#ifndef __STOPWATCH__
#define __STOPWATCH__

#pragma once
#include <Windows.h>
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

	LARGE_INTEGER Frequency;
	bool IsHighResolution;

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
			.addData("frequency", &Stopwatch::Frequency, false)
			.addData("isHighReslution", &Stopwatch::IsHighResolution, false)
			.endClass();
	}

private:
	unsigned int start;

	long elapsed;
	long startTimeStamp;
	long isRunning;
	double tickFrequency;

	long GetTimestamp();
	long GetElapsedDateTimeTicks();
	long GetRawElapsedTicks();
};

const long TicksPerMillisecond = 10000;
const long TicksPerSecond = TicksPerMillisecond * 1000;

Stopwatch::Stopwatch()
{
	BOOL success = QueryPerformanceFrequency(&Frequency);
	if (!success)
	{
		IsHighResolution = false;
		LARGE_INTEGER tps = { TicksPerSecond };
		Frequency = tps;
		tickFrequency = 1;
	}
	else
	{
		IsHighResolution = true;
		LARGE_INTEGER tps = { TicksPerSecond };
		Frequency = tps;
		tickFrequency = TicksPerSecond;
		tickFrequency /= Frequency.QuadPart;
	}
	Reset();
}

void Stopwatch::Start()
{
	if (!isRunning)
	{
		startTimeStamp = GetTimestamp();

		isRunning = true;
	}
}

void Stopwatch::Stop()
{
	if (isRunning)
	{
		long endTimestamp = GetTimestamp();
		long elapsedThisPeriod = endTimestamp - startTimeStamp;
		elapsed += elapsedThisPeriod;

		isRunning = false;
		if (elapsed < 0) elapsed = 0;
	}
}

void Stopwatch::Reset()
{
	elapsed = 0;
	isRunning = false;
	startTimeStamp = 0;
}

void Stopwatch::Restart()
{
	elapsed = 0;
	isRunning = true;
	startTimeStamp = GetTimestamp();
}

int Stopwatch::ElapsedMillis()
{
	return GetElapsedDateTimeTicks() / TicksPerMillisecond;
}

long Stopwatch::GetTimestamp()
{
	if (IsHighResolution)
	{
		LARGE_INTEGER timestamp = { 0 };
		QueryPerformanceCounter(&timestamp);
		return (long)timestamp.QuadPart;
	}
	else
	{
		return -1;
	}
}

long Stopwatch::GetRawElapsedTicks()
{
	long timeElapsed = elapsed;
	if (isRunning)
	{
		long current = GetTimestamp();
		long elapsedUntilNow = current - startTimeStamp;
		timeElapsed += elapsedUntilNow;
	}
	return timeElapsed;
}

#pragma unmanaged
long Stopwatch::GetElapsedDateTimeTicks()
{
	long rawTicks = GetRawElapsedTicks();
	if (IsHighResolution) {
		// convert high resolution perf counter to DateTime ticks
		double dticks = rawTicks;
		dticks *= tickFrequency;
		return (long)dticks;
	}
	else {
		return rawTicks;
	}
}

#endif //__STOPWATCH__