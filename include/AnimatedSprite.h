// File: AnimatedSprite.h
// Class: AnimatedSprite
// Author: Diego Lopes <diego95lopes@live.com>
// 20/03/2015
#ifndef __NIX_ANIMATEDSPRITE__
#define __NIX_ANIMATEDSPRITE__
#pragma once

#include "Node.h"
#include "Stopwatch.h"

class AnimatedSprite :
	public Node
{
public:
	AnimatedSprite(Texture* sheet = 0, int rows = 1, int cols = 1, float speed = 0, bool loop = false);
	virtual ~AnimatedSprite();

	int getRows() const { return m_rows; }
	void setRows(int val) { m_rows = val; }
	int getCols() const { return m_cols; }
	void setCols(int val) { m_cols = val; }
	float getSpeed() const { return m_speed; }
	void setSpeed(float val) { m_speed = val; }
	bool getLoop() const { return m_loop; }
	void setLoop(bool val) { m_loop = val; }
	Texture* getSpriteSheet() const { return m_sheet; }
	void setSpriteSheet(Texture* val) { m_sheet = val; }
	int getIndex() const { return m_index; }

	void step();
    void draw(SceneTree* tree);
	void update(float delta);
    bool hovered(point mousepos);

	static void RegisterObject(lua_State* L);
private:
	int m_rows, m_cols;
	int m_index;
	float m_speed;
	bool m_loop;

	Texture* m_sheet;
	Shader* m_shader;
	Stopwatch m_clock;

        AnimatedSprite(AnimatedSprite&) {}
	void operator=(AnimatedSprite texture) {}
};

#endif //__NIX_ANIMATEDSPRITE__
