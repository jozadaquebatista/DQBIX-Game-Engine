#ifndef __IX_OCCLUDER__
#define __IX_OCCLUDER__
#pragma once

#include <cmath>
#include "lua.hpp"

class occluder
{ };

class boxoccluder : public occluder
{
public:
	boxoccluder(int _x, int _y, int _w, int _h)
		: x(_x), y(_y), w(_w), h(_h)
	{
		
	}

	int getX() const { return x; }
	void setX(int val) { x = val; }

	int getY() const { return y; }
	void setY(int val) { y = val; }

	int getW() const { return w; }
	void setW(int val) { w = val; }

	int getH() const { return h; }
	void setH(int val) { h = val; }

	static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<boxoccluder>("boxoccluder")
			.addConstructor<void(*)(int, int, int, int)>()
			.addProperty("x", &boxoccluder::getX, &boxoccluder::setX)
			.addProperty("y", &boxoccluder::getY, &boxoccluder::setY)
			.addProperty("width", &boxoccluder::getW, &boxoccluder::setW)
			.addProperty("height", &boxoccluder::getH, &boxoccluder::setH)
			.endClass();

	}
private:
	int x, y, w, h;
};

#endif //__IX_OCCLUDER__