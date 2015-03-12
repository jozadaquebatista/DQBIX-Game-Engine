#ifndef __IX_LIGHT__
#define __IX_LIGHT__
#pragma once

#include "lua.hpp"
#include "color.h"

class light
{
public:
	light(int _x, int _y, float r, float g, float b) 
	: x(_x), y(_y)
	{
		_color = new color();
		_color->r = r;
		_color->g = g;
		_color->b = b;
		_color->a = 1.0f;

		_intensity = 1.0f;
		_radius = 1.0f;
		_castshadow = true;
	}

	int getX() const { return x; }
	void setX(int val) { x = val; }
	int getY() const { return y; }
	void setY(int val) { y = val; }
	color* getColor() const { return _color; }
	void setColor(color* val) { _color = val; }
	float getIntensity() const { return _intensity; }
	void setIntensity(float val) { _intensity = val; }
	bool getCastshadow() const { return _castshadow; }
	void setCastshadow(bool val) { _castshadow = val; }
	float getRadius() const { return _radius; }
	void setRadius(float val) { _radius = val; }

	static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<light>("light")
			.addConstructor<void(*)(int, int, float, float, float)>()
			.addProperty("x", &light::getX, &light::setX)
			.addProperty("y", &light::getY, &light::setY)
			.addProperty("color", &light::getColor, &light::setColor)
			.addProperty("shadow", &light::getCastshadow, &light::setCastshadow)
			.addProperty("radius", &light::getRadius, &light::setRadius)
			.addProperty("intensity", &light::getIntensity, &light::setIntensity)
			.endClass();
	}
private:
	int x, y;
	color* _color;
	bool _castshadow;
	float _intensity, _radius;
	
};

#endif //__IX_LIGHT__