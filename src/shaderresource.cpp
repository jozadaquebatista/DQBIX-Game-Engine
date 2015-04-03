#include "../include/shaderresource.h"

shaderResource::shaderResource(int program)
{
    if (program == -1)
        m_program = glCreateProgram();
    else
        m_program = program;

    refCount = 1;

    if (m_program == 0)
    {
        std::cerr << "Shader creation failed: Could not find valid memory location." << std::endl;
        std::exit(-1);
    }
}

shaderResource::~shaderResource()
{
    glDeleteProgram(m_program);
}

void shaderResource::addReference()
{
    refCount++;
}

bool shaderResource::removeReference()
{
    refCount--;
    return refCount == 0;
}

GLuint shaderResource::getProgram() const
{
    return m_program;
}
std::map<std::string, int> shaderResource::getUniforms()
{
    return uniforms;
}

int shaderResource::findUniform(std::string name)
{
    auto pos = uniforms.find(name);
    if (pos != uniforms.end())
        return pos->second;
    return -1;
}

void shaderResource::addUniform(std::string name)
{
    int uloc = -1;
    uloc = glGetUniformLocation(m_program, name.c_str());

    if (uloc == -1)
    {
        printf("Could not find uniform: %s\n", name.c_str());
    }
    uniforms.insert({ name, uloc });
}
