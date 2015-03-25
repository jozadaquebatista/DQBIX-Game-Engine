#ifndef SIMPLEMOVE_H
#define SIMPLEMOVE_H
#pragma once

#include "component.h"
#include "Input.h"
class SimpleMove : public Component
{
public:
    SimpleMove();
    ~SimpleMove();

    void update(float delta);
};

#endif // SIMPLEMOVE_H
