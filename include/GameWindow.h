// ===============================================
// File: Window.h
// Class: Window
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_WINDOW__
#define __NIX_WINDOW__
#pragma once

#include "AnimatedSprite.h"
#include "Sprite.h"
#include "SceneTree.h"
#include "RenderUtil.h"
#include "Time.h"
#include "Input.h"
#include "sdl_backend.h"
#include "audio.h"
#include "light.h"
#include <string>

class GameWindow
{

public:
    GameWindow() : m_tree(0);
    ~GameWindow();

	void createWindow(int width, int height, string title);

	bool closed();
	int getWidth();
	int getHeight();
	float getAspect();
	string getTitle();
    void setTitle(string newtitle);
	
	void(*init)();
	void mainloop();

	static mat4 Projection;

	SceneTree* getTree() { return m_tree; }
    Node* createNode()
    {
        Node* ret = new Node();
        ret->setEngine(this);
        return ret;
    }

	LuaEngine* getLuaEngine() { return eng; }

    static void RegisterObject(lua_State* L);

    float getFps() const;
    void useAsRenderTarget();

    Color getAmbient() const;
    void setAmbient(const Color &getAmbient);

private:
    GameWindow(GameWindow& win) {}
    void operator=(GameWindow win) {}

    float fps;
    void ortho_2d(float* mat, int left, int right, int bottom, int top);
	SceneTree* m_tree;
    LuaEngine* eng;
    Color m_ambient;

};

#endif //__NIX_WINDOW__
