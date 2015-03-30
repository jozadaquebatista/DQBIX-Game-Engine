#ifndef __IX_COLOR__
#define __IX_COLOR__
#pragma once

#include "lua.hpp"
typedef struct Color
{
    float r, g, b, a;
    Color(float ar=1.0f, float ag=1.0f, float ab=1.0f, float aa=1.0f)
    {
        r = ar;
        g = ag;
        b = ab;
        a = aa;
    }

    static void RegisterObject(lua_State* L);
} Color;

#endif //__IX_COLOR__
