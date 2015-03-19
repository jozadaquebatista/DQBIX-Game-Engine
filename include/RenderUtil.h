// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: RenderUtil.h
// Class: RenderUtil
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_RENDERUTIL__
#define __NIX_RENDERUTIL__
#pragma once

#include "graphics.h"

class RenderUtil
{
public:
	static void clearScreen();
	static void initGraphics(int w, int h);
};

#endif //__NIX_RENDERUTIL__