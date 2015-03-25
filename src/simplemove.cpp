#include "include/simplemove.h"

SimpleMove::SimpleMove()
{

}

SimpleMove::~SimpleMove()
{

}

void SimpleMove::update(float delta)
{
    if (Input::getKey(SDLK_UP))
    {
        getTransform()->move(0.0f, -3.0f, 0.0f);
    }
    if (Input::getKey(SDLK_DOWN))
    {
        getTransform()->move(0.0f, 3.0f, 0.0f);
    }
    if (Input::getKey(SDLK_LEFT))
    {
        getTransform()->move(-3.0f, 0.0f, 0.0f);
    }
    if (Input::getKey(SDLK_RIGHT))
    {
        getTransform()->move(3.0f, 0.0f, 0.0f);
    }
}

