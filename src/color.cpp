#include "../include/color.h"

void Color::RegisterObject(lua_State *L)
{
    using namespace luabridge;
    getGlobalNamespace(L)
            .beginClass<Color>("Color")
            .addConstructor<void(*)(float, float, float, float)>()
            .addData("r", &Color::r)
            .addData("g", &Color::g)
            .addData("b", &Color::b)
            .addData("a", &Color::a)
            .endClass();
}
