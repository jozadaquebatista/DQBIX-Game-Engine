// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: Game.h
// Class: Game
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_GAME__
#define __NIX_GAME__
#pragma once

#include "Input.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void input() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif //__NIX_TIME__