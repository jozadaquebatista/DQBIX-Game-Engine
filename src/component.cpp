#include "../include/component.h"
#include "../include/GameWindow.h"
#include "../include/Node.h"

Component::Component() : m_owner(0), m_script(0)
{

}

Component::~Component()
{
    SAFE_DELETE(m_script);
}

void Component::setOwner(Node *own) { m_owner = own; }

Node *Component::getOwner() { return m_owner; }

Transform *Component::getTransform() const { return m_owner->getTransform(); }

void Component::create()
{
    if (m_script != NULL)
        m_script->init();
}

void Component::destroy()
{
    if (m_script != NULL)
        m_script->destroy();
}

void Component::update(float delta)
{
    if (m_script != NULL)
        m_script->update(delta);
}

void Component::attachScript(Script *scr)
{
    if (scr != nullptr)
    {
        m_script = new Script(*scr);
        m_script->setOwner(this);
        m_script->compile();
    }
    else { m_script = nullptr; }
}

