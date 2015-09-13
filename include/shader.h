#ifndef __IX_SHADER__
#define __IX_SHADER__
#pragma once

#include <iostream>
#include <fstream>
#include <streambuf>

#include "lua.hpp"
#include "shaderresource.h"
#include "shaders.h"

struct StringHelper {
	const char *p;
	StringHelper(const string& s) : p(s.c_str()) {}
	operator const char**() { return &p; }
};

class Shader
{

public:
    Shader() : Shader(default_frag)
	{

	}
	Shader(string vs, string fs);
	Shader(string fs);

	void use();
	void compile();

	void setFloat(string name, float val);
	void setInt(string name, int val);
	void setVec2(string name, float x, float y);
	void setVec3(string name, float x, float y, float z);
	void setVec4(string name, float x, float y, float z, float w);
	void setMatrix(string name, mat4 mat);
	
	void addUniform(string name);
	void addCommonUniforms();
	void loadUniforms();
	
	virtual ~Shader();

	Shader* fromString(string vs, std::string fs);

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<Shader>("shader")
			.addConstructor<void(*)(std::string, std::string)>()
			.addConstructor<void(*)(std::string)>()
			.addFunction("use", &Shader::use)
			.addFunction("loaduniforms", &Shader::loadUniforms)
			.addFunction("compile", &Shader::compile)
			.addFunction("setfloat", &Shader::setFloat)
			.addFunction("setint", &Shader::setInt)
			.addFunction("setvec2", &Shader::setVec2)
			.addFunction("setvec3", &Shader::setVec3)
			.addFunction("setvec4", &Shader::setVec4)
			.addFunction("adduniform", &Shader::addUniform)
			.endClass();
	}
private:
    Shader(Shader&) {}
    void operator=(Shader s) {}

    map<string, shaderResource*> loadedshaders;
    shaderResource* m_resource;

	string loadShaderData(string filename);

    void addShader(string text, int type);
    
};

#endif //__IX_SHADER__
