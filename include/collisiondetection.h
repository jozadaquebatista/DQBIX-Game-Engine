#ifndef __IX_COLLISION_DETECT__
#define __IX_COLLISION_DETECT__

#pragma once

#include "point.hpp"
#include <math.h>
#include <string>

class collisiondetection
{

public:
	static bool box(int x1, int y1, int w1, int h1,
					int x2, int y2, int w2, int h2);
	static bool circle(int x1, int y1, int r1, int x2, int y2, int r2);
	static string side(point pos, point sz, point delta, point opos, point osz);
	static string _side(int x, int y, int w, int h, int dx, int dy, int ox, int oy, int ow, int oh);

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("collisions")
			.addFunction("box", &collisiondetection::box)
			.addFunction("circle", &collisiondetection::circle)
			.addFunction("side", &collisiondetection::side)
			.endNamespace();
	}
};

#endif //__IX_COLLISION_DETECT__
