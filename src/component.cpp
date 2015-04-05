#include "../include/component.h"
#include "../include/GameWindow.h"
#include "../include/Node.h"

Component::Component() : m_owner(0)
{

}

Component::~Component()
{

}

void Component::setOwner(Node *own) { m_owner = own; }

Node *Component::getOwner() { return m_owner; }

Transform *Component::getTransform() const
{
    return m_owner->getTransform();
}
