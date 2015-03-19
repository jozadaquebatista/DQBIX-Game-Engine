#ifndef TEST_GAME
#define TEST_GAME
#pragma once

#include "Game.h"

class TestGame :
	public Game
{
public:
	TestGame();
	~TestGame();

	void input();
	void update();
	void render();
};

#endif