#ifndef SHADERRESOURCE_H
#define SHADERRESOURCE_H
#pragma once

#include "graphics.h"
#include <iostream>
#include <map>
#include <string>

class shaderResource
{

public:
    shaderResource(int program = -1);
    virtual ~shaderResource();

    void addReference();
    bool removeReference();

    GLuint getProgram() const;

    map<string, int> getUniforms();
    int findUniform(string name);
    void addUniform(string name);

private:
    shaderResource(shaderResource&) {}
    void operator=(shaderResource) {}

    map<string, int> uniforms;
    int refCount;

    GLuint m_program;
    
};

#endif // SHADERRESOURCE_H
