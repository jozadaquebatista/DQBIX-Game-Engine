#include "../include/shader.h"


void Shader::addUniform(std::string name)
{
    if (!m_resource) return;

    m_resource->addUniform(name);
}


void Shader::addCommonUniforms()
{
	addUniform("proj");
	addUniform("model");
}

void Shader::loadUniforms()
{
	addCommonUniforms();
	addUniform("image");
	addUniform("cliprect");
}

Shader::~Shader()
{
    SAFE_DELETE(m_resource);
}

Shader::Shader(std::string fs)
{
	fromString(default_vert, loadShaderData(fs));
}

Shader* Shader::fromString(std::string vs, std::string fs)
{
    std::map<std::string, shaderResource*>::const_iterator pos = loadedshaders.find(vs + "|||" + fs);
    if (pos == loadedshaders.cend())
    {
        m_resource = new shaderResource();

        addShader(vs, GL_VERTEX_SHADER);
        addShader(fs, GL_FRAGMENT_SHADER);

        if (vs == "" && fs == "") return NULL;

        compile();

        loadedshaders.insert( {vs + "|" + fs, m_resource} );
    }
    else
    {
        m_resource = pos->second;
        m_resource->addReference();
    }
    return this;
}

Shader::Shader(std::string vs /*= ""*/, std::string fs /*= ""*/)
{
    std::string svs = loadShaderData(vs);
    std::string sfs = loadShaderData(fs);
    fromString(svs, sfs);
}

void Shader::use()
{
    if (!m_resource) return;
    glUseProgram(m_resource->getProgram());
}

void Shader::compile()
{
    if (!m_resource) return;

    GLint status;
    GLuint program = m_resource->getProgram();

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (!status)
	{
		GLchar log[1024];
        glGetProgramInfoLog(program, 1024, NULL, log);
		fprintf(stderr, "Program Error:\n%s", log);
		exit(EXIT_FAILURE);
	}

    glValidateProgram(program);

    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (!status)
	{
		GLchar log[1024];
        glGetShaderInfoLog(program, 1024, NULL, log);
		printf("Shader Error:\n%s", log);
		exit(EXIT_FAILURE);
	}
}

void Shader::setFloat(std::string name, float val)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniform1f(unif, val);
	}
	else
	{
        printf("Could not find FLOAT uniform: %s.\n", name.c_str());
	}
}

void Shader::setInt(std::string name, int val)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniform1iv(unif, 1, &val);
	}
	else
	{
        printf("Could not find INT uniform: %s.\n", name.c_str());
	}
}

void Shader::setVec2(std::string name, float x, float y)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniform2f(unif, x, y);
	}
	else
	{
        printf("Could not find VEC2 uniform: %s.\n", name.c_str());
	}
}

void Shader::setVec3(std::string name, float x, float y, float z)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniform3f(unif, x, y, z);
	}
	else
	{
        printf("Could not find VEC3 uniform: %s.\n", name.c_str());
	}
}

void Shader::setVec4(std::string name, float x, float y, float z, float w)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniform4f(unif, x, y, z, w);
	}
	else
	{
        printf("Could not find VEC4 uniform: %s.\n", name.c_str());
	}
}

void Shader::setMatrix(std::string name, mat4 mat)
{
    int unif = m_resource->findUniform(name);
    if (unif != -1)
	{
        glUniformMatrix4fv(unif, 1, false, value_ptr(mat));
	}
	else
	{
        printf("Could not find MATRIX uniform: %s.\n", name.c_str());
	}
}

std::string Shader::loadShaderData(std::string filename)
{
	std::ifstream t(filename);
	std::string str((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());
	return str;
}

void Shader::addShader(std::string text, int type)
{
    if (!m_resource) return;
    if (text != "")
    {
        const GLchar* v[1];
        v[0] = text.c_str();
        GLint vlengths[1];
        vlengths[0] = text.size();

        GLuint m_shad = glCreateShader(type);
        glShaderSource(m_shad, 1, v, vlengths);
        glCompileShader(m_shad);

        GLint status;
        glGetShaderiv(m_shad, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            GLchar log[1024];
            glGetShaderInfoLog(m_shad, 1024, NULL, log);
            fprintf(stderr, "Shader Error:\n%s", log);
            exit(EXIT_FAILURE);
        }
        glAttachShader(m_resource->getProgram(), m_shad);
    }
}
