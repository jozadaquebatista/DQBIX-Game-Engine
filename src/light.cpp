#include "../include/light.h"
#include "../include/GameWindow.h"

void Light::addToEngine(GameWindow *eng)
{
    eng->getTree()->addLight(this);
}
float Light::getRadius() const
{
    return m_radius;
}

void Light::setRadius(float radius)
{
    m_radius = radius;
}

