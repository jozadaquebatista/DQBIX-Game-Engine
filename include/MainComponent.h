// THIS FILE IS PART OF THE NEW ENGINE PROJECT
// IF YOU WANT TO USE THE OLD ENGINE, YOU NEED TO
// DEFINE OLD_ENGINE ON main.cpp
// ===============================================
// File: MainComponent.h
// Class: MainComponent
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_MAIN__
#define __NIX_MAIN__
#pragma once

#include "RenderUtil.h"
#include "Window.h"
#include "Time.h"
#include "Game.h"
#include "Input.h"

class MainComponent
{
public:
	MainComponent(Game* game);

	void start();
	void stop();

	virtual ~MainComponent();
private:
	void run();
	void render();
	void clean();
	bool running;

	static float FRAME_CAP;
	Game* m_game;
};

#endif //__NIX_MAIN__