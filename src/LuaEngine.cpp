#include "../include/LuaEngine.hpp"

void LuaEngine::err_report(int state)
{
	if (state != 0)
	{
        IXLOG("SCRIPT: Lua Error: ", LOG_ERROR, false);
        IXLOG(lua_tostring(L, state), LOG_PLAIN, true);

		lua_pop(L, 1);
        std::exit(-1);
	}
}

void LuaEngine::RunScript(const char* filename)
{
    if (filename == "")
		return;
	int state = luaL_dofile(L, filename);
	err_report(state);
}

void LuaEngine::RunString(const char* expr)
{
    if (expr == NULL)
	{
        IXLOG("Error: ", LOG_ERROR, false);
        IXLOG("Null expression is not allowed.", LOG_PLAIN, true);

        std::exit(-1);
	}
	int state = luaL_dostring(L, expr);
	err_report(state);
}

