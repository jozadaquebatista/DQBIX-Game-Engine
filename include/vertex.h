#ifndef __IX_VERTEX__
#define __IX_VERTEX__
#pragma once

#include "graphics.h"

class vertex
{
public:
	vertex(vec3 pos, vec2 tex) : m_position(pos), m_texcoord(tex);

	vec3 getPosition() const { return m_position; }
	void setPosition(const vec3& pos) { m_position = pos; }

	vec2 getTexCoord() const { return m_texcoord; }
	void setTexCoord(const vec2& tex) { m_texcoord = tex; }

	vec3 getTangent() const { return m_tangent; }
	void setTangent(const vec3& tang) { m_tangent = tang; }

	vec3 getNormal() const { return m_normal; }
	void setNormal(const vec3& norm) { m_normal = norm; }

	static const int SIZE = 12;
private:
	vec3 m_position;
	vec2 m_texcoord;
	vec3 m_normal;
	vec3 m_tangent;
};

#endif //__IX_VERTEX__
