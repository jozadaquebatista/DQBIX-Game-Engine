// File: Sprite.h
// Class: Sprite
// Author: Diego Lopes <diego95lopes@live.com>
// 19/03/2015
#ifndef __NIX_SPRITE__
#define __NIX_SPRITE__
#pragma once

#include "Node.h"

class Sprite : public Node
{
public:
	Sprite(std::string filename);
	virtual ~Sprite();

	void draw();

	Texture* getTexture() const { return m_texture; }
	void setTexture(Texture* tex) { m_texture = tex; }

	static void RegisterObject(lua_State* L);
private:
	Shader* m_shader;
	Texture* m_texture;
};

#endif //__NIX_SPRITE__