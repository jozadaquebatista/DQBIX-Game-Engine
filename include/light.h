#ifndef __IX_LIGHT__
#define __IX_LIGHT__
#pragma once

#include "lua.hpp"
#include "color.h"
#include "component.h"

class Light : public Component
{
public:
    Light(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f)
	{
        _color = new Color();
		_color->r = r;
		_color->g = g;
		_color->b = b;
		_color->a = a;

        _castshadow = false;
	}

    Color* getColor() const { return _color; }
    void setColor(Color* val) { _color = val; }

	bool getCastshadow() const { return _castshadow; }
	void setCastshadow(bool val) { _castshadow = val; }

	float getConstant() const { return fx; }
	float getLinear() const { return fy; }
	float getQuadratic() const { return fz; }
	void setConstant(float v) { fx = v; }
	void setLinear(float v) { fy = v; }
	void setQuadratic(float v) { fz = v; }

    static void RegisterObject(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
            .beginClass<Light>("light")
            .addConstructor<void(*)(float, float, float, float)>()
            .addProperty("color", &Light::getColor, &Light::setColor)
            .addProperty("constant", &Light::getConstant, &Light::setConstant)
            .addProperty("linear", &Light::getLinear, &Light::setLinear)
            .addProperty("quadratic", &Light::getQuadratic, &Light::setQuadratic)
			.endClass();
	}
private:
    Color* _color;
	bool _castshadow;

	float fx, fy, fz;
};

#endif //__IX_LIGHT__
