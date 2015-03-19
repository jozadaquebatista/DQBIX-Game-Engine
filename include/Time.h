// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: Time.h
// Class: Time
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_TIME__
#define __NIX_TIME__
#pragma once

#include "sdl_backend.h"
class Time
{
public:
	static const int SECOND = 1000;

	static int getTime();
	static float getDelta();
	static void setDelta(float d);
private:
	static float m_delta;
};

#endif //__NIX_TIME__