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
        _color.r = r;
        _color.g = g;
        _color.b = b;
        _color.a = a;

        _castshadow = false;

        intens = 160.0f;
	}

    Color getColor() const { return _color; }
    void setColor(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f)
    {
        _color.r = r;
        _color.g = g;
        _color.b = b;
        _color.a = a;
    }

	bool getCastshadow() const { return _castshadow; }
	void setCastshadow(bool val) { _castshadow = val; }

    void addToEngine(GameWindow* eng);

	float getConstant() const { return fx; }
	float getLinear() const { return fy; }
	float getQuadratic() const { return fz; }
	void setConstant(float v) { fx = v; }
	void setLinear(float v) { fy = v; }
	void setQuadratic(float v) { fz = v; }

    float getIntensity() const { return intens; }
    void setIntensity(float i) { intens = i; }

    static void RegisterObject(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
            .beginClass<Light>("light")
            .addConstructor<void(*)(float, float, float, float)>()
            .addFunction("setcolor", &Light::setColor)
            .addFunction("getcolor", &Light::getColor)
            .addProperty("constant", &Light::getConstant, &Light::setConstant)
            .addProperty("linear", &Light::getLinear, &Light::setLinear)
            .addProperty("quadratic", &Light::getQuadratic, &Light::setQuadratic)
            .addProperty("intensity", &Light::getIntensity, &Light::setIntensity)
			.endClass();
	}
private:
    Color _color;
	bool _castshadow;

	float fx, fy, fz;
    float intens;
};

#endif //__IX_LIGHT__
