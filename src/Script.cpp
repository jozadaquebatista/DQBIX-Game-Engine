#include "../include/Script.h"
#include "../include/component.h"

Script::Script(std::string scriptfile, LuaEngine* L)
    : m_L(L),
    on_destroy(m_L->getState()),
    on_create(m_L->getState()),
    on_update(m_L->getState()),
	m_owner(0)
{
	m_source = readFile(scriptfile);
}

Script::~Script()
{

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
		on_create(m_owner);
}

void Script::update(float delta)
{
	if (on_update.isFunction())
		on_update(m_owner, delta);
}

void Script::destroy()
{
	if (on_destroy.isFunction())
		on_destroy(m_owner);
}

void Script::setOwner(Component* own)
{
	m_owner = own;
}

Component* Script::getOwner() const
{
	return m_owner;
}
