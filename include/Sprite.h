// File: GameObject.h
// Class: GameObject
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_GAMEOBJECT__
#define __NIX_GAMEOBJECT__
#pragma once

#include "Transform.h"
#include "Texture.h"
#include "shader.h"
#include <vector>

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	Sprite* addChild(Sprite* obj);

	Transform* getTransform() const { return m_transform; }
	
	void update();
	void updateAll();
	void draw();
	void drawAll();
private:
	shader* m_shader;
	Texture* m_texture;
	Transform* m_transform;
	std::vector<Sprite*> m_children;
};

#endif //__NIX_GAMEOBJECT__