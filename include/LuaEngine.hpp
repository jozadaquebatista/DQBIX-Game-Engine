#ifndef __LUA_ENGINE_DQBIX__
#define __LUA_ENGINE_DQBIX__
#pragma once
#include <vector>
#include <iostream>

#include "lua.hpp"
#include <cstdlib>

class LuaEngine
{
public:
	LuaEngine() : L(luaL_newstate())
	{
		luaL_openlibs(L);
	}
	~LuaEngine()
	{
		lua_close(L);
	}	

	lua_State* getState() { return L; }

	void RunScript(const char* filename);
	void RunString(const char* expr);

private:
	lua_State* L;
	void err_report(int state);
};
#endif //__LUA_ENGINE_DQBIX__
