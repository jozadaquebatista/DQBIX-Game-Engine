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
        if (IsType<AnimatedSprite>(m_owner))
            on_create((AnimatedSprite*)m_owner);
        else
            on_create(m_owner);
    }
}

void Script::update(float delta)
{
	if (on_update.isFunction())
    {
        if (IsType<AnimatedSprite>(m_owner))
            on_update((AnimatedSprite*)m_owner, delta);
        else
            on_update(m_owner, delta);
    }
}

void Script::destroy()
{
	if (on_destroy.isFunction())
    {
        if (IsType<AnimatedSprite>(m_owner))
            on_destroy((AnimatedSprite*)m_owner);
        else
            on_destroy(m_owner);
    }
}
