#ifndef __IX_POINT__
#define __IX_POINT__
#pragma once

#include "lua.hpp"

class point
{

public:
	point() {}
	point(float px, float py) : x(px), y(py) {}

	float x, y;

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<point>("point")
			.addConstructor<void(*)(void)>()
			.addConstructor<void(*)(float, float)>()
			.addData("x", &point::x, true)
			.addData("y", &point::y, true)
			.endClass();
	}
	
};

#endif //__IX_POINT__
