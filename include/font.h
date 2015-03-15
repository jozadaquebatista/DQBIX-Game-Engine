#ifndef __IX_FONT__
#define __IX_FONT__
#pragma once

#include "point.hpp"
#include "graphics.h"

#include <drawtext.h>

class font
{
public:
	font(std::string fontfile = "", int sz = 18);

	point* measure_string(std::string str);
	void set_range(int from, int to);
	void use();

	virtual ~font();

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<font>("font")
			.addConstructor<void(*)(std::string, int)>()
			.addFunction("measurestring", &font::measure_string)
			.addFunction("setrange", &font::set_range)
			.addFunction("use", &font::use)
			.endClass();
	}
private:
	void operator=(font f) {}
	font(font& f) {}
	int sz;
	struct dtx_font* fnth;
};

#endif // __IX_FONT__