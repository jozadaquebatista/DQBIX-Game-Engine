#include "../include/light.h"
#include "../include/GameWindow.h"

void Light::addToEngine(GameWindow *eng)
{
    eng->getTree()->addLight(this);
}
