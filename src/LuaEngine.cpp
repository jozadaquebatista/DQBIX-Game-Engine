#include "../include/LuaEngine.hpp"

void LuaEngine::err_report(int state)
{
	if (state != 0)
	{
		std::cout << "ERROR -> " << lua_tostring(L, state) << std::endl;
		lua_pop(L, 1);
        std::exit(-1);
	}
}

void LuaEngine::RunScript(const char* filename)
{
    if (filename == NULL)
		return;
	int state = luaL_dofile(L, filename);
	err_report(state);
}

void LuaEngine::RunString(const char* expr)
{
    if (expr == NULL)
	{
		std::cerr << "Null expression is not allowed." << std::endl;
		return;
	}
	int state = luaL_dostring(L, expr);
	err_report(state);
}
