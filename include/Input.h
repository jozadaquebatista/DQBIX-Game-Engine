// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: Input.h
// Class: Input
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_INPUT__
#define __NIX_INPUT__
#pragma once

#include <vector>
#include "sdl_backend.h"
#include "graphics.h"
#include "point.hpp"
#include "lua.hpp"

class Input
{
public:
	static void update();

	static bool getKey(int keycode);
	static bool getKeyDown(int keycode);
	static bool getKeyUp(int keycode);
	static bool getMouse(int btncode);
	static bool getMouseDown(int btncode);
	static bool getMouseUp(int btncode);
	static point getMousePosition();
	static void setMousePosition(float x, float y);
	static void setCursor(bool cur);

	static void RegisterObject(lua_State* L);

	static SDL_Event evt;
private:
	static bool downKeys[];
	static bool upKeys[];
	static bool inputs[];

	static bool downMouse[];
	static bool upMouse[];
	static bool mouseInputs[];
	static int mX;
	static int mY;

	static const int NUMKEYS = 512;
	static const int NUMMOUSEBUTTONS = 256;	
};

#endif //__NIX_INPUT__