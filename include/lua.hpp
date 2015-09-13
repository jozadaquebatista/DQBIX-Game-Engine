#ifndef __IX_LUA__
#define __IX_LUA__
#pragma once

extern "C" {

    #include <lua5.2/lua.h>
    #include <lua5.2/lauxlib.h>
    #include <lua5.2/lualib.h>
    
}

#include <LuaBridge.h>

#define SAFE_DELETE(x) { if(x) delete x; x = NULL; }
#endif //__IX_LUA__
