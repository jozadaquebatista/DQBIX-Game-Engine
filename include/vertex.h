#ifndef __IX_VERTEX__
#define __IX_VERTEX__
#pragma once

#include "graphics.h"

class vertex
{
public:
	vertex(vec3 pos, vec2 tex) : m_position(pos), m_texcoord(tex)
	{}

	vec3 getPosition() const { return m_position; }
	void setPosition(const vec3& pos) { m_position = pos; }

	vec2 getTexCoord() const { return m_texcoord; }
	void setTexCoord(const vec2& tex) { m_texcoord = tex; }

	static const int SIZE = 5;
private:
	vec3 m_position;
	vec2 m_texcoord;
};

#endif //__IX_VERTEX__