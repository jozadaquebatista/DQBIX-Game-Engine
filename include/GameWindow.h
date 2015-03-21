// ===============================================
// File: Window.h
// Class: Window
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_WINDOW__
#define __NIX_WINDOW__
#pragma once

#include "SceneTree.h"
#include "RenderUtil.h"
#include "Time.h"
#include "Input.h"
#include "sdl_backend.h"
#include <string>

class GameWindow
{
public:
	GameWindow() : m_tree(0) {};

	void createWindow(int width, int height, std::string title);

	bool closed();
	int getWidth();
	int getHeight();
	float getAspect();
	std::string getTitle();
	
	void(*init)();

	void mainloop();

	static mat4 Projection;

	SceneTree* getTree() { return m_tree; }
private:
	void ortho_2d(float* mat, int left, int right, int bottom, int top);
	SceneTree* m_tree;
};

#endif //__NIX_WINDOW__