// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: Window.h
// Class: Window
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_WINDOW__
#define __NIX_WINDOW__
#pragma once

#include "graphics.h"
#include "sdl_backend.h"
#include "Input.h"
#include <string>

class Window
{
public:
	static void createWindow(int width, int height, std::string title);
	static void render();
	static bool closed();
	static int getWidth();
	static int getHeight();
	static float getAspect();
	static std::string getTitle();
	
};

#endif //__NIX_WINDOW__