#include "..\include\Time.h"
float Time::m_delta = 0.0f;

int Time::getTime()
{
	return SDL_GetTicks();
}

float Time::getDelta()
{
	return m_delta;
}

void Time::setDelta(float d)
{
	Time::m_delta = d;
}