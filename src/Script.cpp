#include "../include/Script.h"
#include "../include/Node.h"
#include "../include/AnimatedSprite.h"

Script::Script(std::string scriptsource, LuaEngine* L)
    : m_L(L),
    on_destroy(m_L->getState()),
    on_create(m_L->getState()),
    on_update(m_L->getState()),
	m_owner(0)
{
    m_source = scriptsource;
}

void Script::compile()
{
	m_L->RunString(m_source.c_str());

	on_create = luabridge::getGlobal(m_L->getState(), "on_create");
	on_destroy = luabridge::getGlobal(m_L->getState(), "on_destroy");
	on_update = luabridge::getGlobal(m_L->getState(), "on_update");
}

void Script::init()
{
	if (on_create.isFunction())
    {
        try
        {
            if (IsType<AnimatedSprite>(m_owner))
                on_create((AnimatedSprite*)m_owner);
            else
                on_create(m_owner);
        }
        catch (LuaException& e)
        {
            IXLOG("INIT: Lua Error: ", LOG_ERROR, false);
            IXLOG(e.what(), LOG_PLAIN, true);
        }
    }
}

void Script::update(float delta)
{
	if (on_update.isFunction())
    {
        try
        {
            if (IsType<AnimatedSprite>(m_owner))
                on_update((AnimatedSprite*)m_owner, delta);
            else
                on_update(m_owner, delta);
        }
        catch (LuaException &e)
        {
            IXLOG("UPDATE: Lua Error: ", LOG_ERROR, false);
            IXLOG(e.what(), LOG_PLAIN, true);
        }
    }
}

void Script::destroy()
{
	if (on_destroy.isFunction())
    {
        try
        {
            if (IsType<AnimatedSprite>(m_owner))
                on_destroy((AnimatedSprite*)m_owner);
            else
                on_destroy(m_owner);
        }
        catch (LuaException &e)
        {
            IXLOG("DESTROY: Lua Error: ", LOG_ERROR, false);
            IXLOG(e.what(), LOG_PLAIN, true);
        }
    }
}
