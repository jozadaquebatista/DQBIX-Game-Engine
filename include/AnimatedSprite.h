// File: AnimatedSprite.h
// Class: AnimatedSprite
// Author: Diego Lopes <diego95lopes@live.com>
// 20/03/2015
#ifndef __NIX_ANIMATEDSPRITE__
#define __NIX_ANIMATEDSPRITE__
#pragma once

#include "Sprite.h"
#include "Stopwatch.h"
#include <initializer_list>

class Animation
{
public:
    Animation(string name = "anim", initializer_list<int> frames = {}, float speed = 0.04f, bool loop = false) : m_name(name), m_frames(frames), m_speed(speed), m_loop(loop);

    friend class AnimatedSprite;
    
private:
    vector<int> m_frames;
    float m_speed;
    bool m_loop;
    string m_name;
};

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite(Texture* sheet = 0, int rows = 1, int cols = 1);
    AnimatedSprite(Texture* sheet = 0, Texture* sheet_norm = 0, int rows = 1, int cols = 1);

    ~AnimatedSprite()
    {
        for (auto& a : m_animations)
        {
            SAFE_DELETE(a.second);
        }
    }

	int getRows() const { return m_rows; }
	void setRows(int val) { m_rows = val; }
	int getCols() const { return m_cols; }
	void setCols(int val) { m_cols = val; }
	int getIndex() const { return m_index; }

	void step();
    void draw(SceneTree* tree);
	void update(float delta);
    bool hovered(point mousepos);

    void addAnimation(Animation* anim);
    bool removeAnimation(std::string name);
    void setCurrentAnimation(std::string name);

	static void RegisterObject(lua_State* L);

    friend class Animation;
    
private:
	int m_rows, m_cols;
	int m_index;

	Stopwatch m_clock;

    map<std::string, Animation*> m_animations;
    Animation* m_currentAnim;

    AnimatedSprite(AnimatedSprite&) {}
	void operator=(AnimatedSprite texture) {}
};

#endif //__NIX_ANIMATEDSPRITE__
