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

    std::map<std::string, int> getUniforms();
    int findUniform(std::string name);
    void addUniform(std::string name);

private:
    shaderResource(shaderResource& s) {}
    void operator=(shaderResource s) {}

    std::map<std::string, int> uniforms;
    int refCount;

    GLuint m_program;
};

#endif // SHADERRESOURCE_H
