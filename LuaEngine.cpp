#include "LuaEngine.hpp"

void LuaEngine::err_report(int state)
{
	if (state != 0)
	{
		std::cerr << "ERROR -> " << lua_tostring(L, state) << std::endl;
		lua_pop(L, 1);
	}
}

void LuaEngine::RunScript(const char* filename)
{
	if (filename == nullptr)
		return;
	int state = luaL_dofile(L, filename);
	err_report(state);
}

void LuaEngine::RunString(const char* expr)
{
	if (expr == nullptr)
	{
		std::cerr << "Null expression is not allowed." << std::endl;
		return;
	}
	int state = luaL_dostring(L, expr);
	err_report(state);
}