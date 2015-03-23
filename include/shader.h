#ifndef __IX_SHADER__
#define __IX_SHADER__
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <map>

#include "../include/lua.hpp"
#include "../include/graphics.h"
#include "../include/shaders.h"

struct StringHelper {
	const char *p;
	StringHelper(const std::string& s) : p(s.c_str()) {}
	operator const char**() { return &p; }
};

class Shader
{
public:
	Shader() : Shader("")
	{

	}
	Shader(std::string vs, std::string fs);
	Shader(std::string fs);

	void use();
	void compile();

	void setFloat(std::string name, float val);
	void setInt(std::string name, int val);
	void setVec2(std::string name, float x, float y);
	void setVec3(std::string name, float x, float y, float z);
	void setVec4(std::string name, float x, float y, float z, float w);
	void setMatrix(std::string name, mat4 mat);
	
	void addUniform(std::string name);
	void addCommonUniforms();
	void loadUniforms();
	
	virtual ~Shader();

	Shader* fromString(std::string vs, std::string fs);

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
	std::map<std::string, int> uniforms;

	GLuint m_vs, m_fs, m_program;
	std::string loadShaderData(std::string filename);
	static int linecount(std::string t);
};

#endif //__IX_SHADER__
