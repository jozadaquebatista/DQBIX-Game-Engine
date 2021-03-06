// File: Script.h
// Class: Script
// Author: Diego Lopes <diego95lopes@live.com>
// 21/03/2015
#ifndef __NIX_SCRIPT__
#define __NIX_SCRIPT__
#pragma once

#include "LuaEngine.hpp"
#include <LuaBridge/detail/LuaException.h>
#include "Helpers.hpp"
#include <memory>

class Node;

class Script
{
public:
    Script(std::string scriptsource = "", LuaEngine* L = 0);

	void compile();
	void init();
	void update(float delta);
	void destroy();

	LuaEngine* getEngine() { return m_L; }

    void setOwner(Node* own)
    {
        m_owner = own;
    }

    Node* getOwner() const
    {
        return m_owner;
    }

private:
	void operator=(Script s) {}

    string m_source;

	LuaEngine* m_L;

	luabridge::LuaRef on_create;
	luabridge::LuaRef on_destroy;
	luabridge::LuaRef on_update;

    Node* m_owner;
};

#endif //__NIX_SCRIPT__
