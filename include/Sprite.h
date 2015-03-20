// File: GameObject.h
// Class: GameObject
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_GAMEOBJECT__
#define __NIX_GAMEOBJECT__
#pragma once

#include "Node.h"

class Sprite : public Node
{
public:
	Sprite(std::string filename);
	virtual ~Sprite();

	void draw();
private:
	shader* m_shader;
	Texture* m_texture;

};

#endif //__NIX_GAMEOBJECT__