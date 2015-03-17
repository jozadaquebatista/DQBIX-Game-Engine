#ifndef __IX_LIGHT__
#define __IX_LIGHT__
#pragma once

#include "lua.hpp"
#include "color.h"

class light
{
public:
	light(int _x, int _y, float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f) 
	: x(_x), y(_y)
	{
		_color = new color();
		_color->r = r;
		_color->g = g;
		_color->b = b;
		_color->a = a;

		_castshadow = true;
	}

	int getX() const { return x; }
	void setX(int val) { x = val; }
	int getY() const { return y; }
	void setY(int val) { y = val; }
	color* getColor() const { return _color; }
	void setColor(color* val) { _color = val; }

	bool getCastshadow() const { return _castshadow; }
	void setCastshadow(bool val) { _castshadow = val; }

	float getConstant() const { return fx; }
	float getLinear() const { return fy; }
	float getQuadratic() const { return fz; }
	void setConstant(float v) { fx = v; }
	void setLinear(float v) { fy = v; }
	void setQuadratic(float v) { fz = v; }

	static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<light>("light")
			.addConstructor<void(*)(int, int, float, float, float)>()
			.addProperty("x", &light::getX, &light::setX)
			.addProperty("y", &light::getY, &light::setY)
			.addProperty("color", &light::getColor, &light::setColor)
			.addProperty("constant", &light::getConstant, &light::setConstant)
			.addProperty("linear", &light::getLinear, &light::setLinear)
			.addProperty("quadratic", &light::getQuadratic, &light::setQuadratic)
			.endClass();
	}
private:
	int x, y;
	color* _color;
	bool _castshadow;

	float fx, fy, fz;
};

#endif //__IX_LIGHT__