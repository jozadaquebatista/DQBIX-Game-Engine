#ifndef __IX_SHADER__
#define __IX_SHADER__
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <map>

#include "../include/graphics.h"
#include "../include/lua.hpp"
#include "../include/Matrices.h"

struct StringHelper {
	const char *p;
	StringHelper(const std::string& s) : p(s.c_str()) {}
	operator const char**() { return &p; }
};

class shader
{
public:
	shader(std::string vs = "", std::string fs = "");

	void use();
	void compile();

	void setFloat(std::string name, float val);
	void setInt(std::string name, int val);
	void setVec2(std::string name, float x, float y);
	void setVec3(std::string name, float x, float y, float z);
	void setMatrix(std::string name, Matrix4 mat);
	
	void addUniform(std::string name);
	void updateUniforms(Matrix4 model, Matrix4 view_proj);

	virtual ~shader();

	shader* fromString(std::string vs, std::string fs);

	inline static void lua_reg(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginClass<shader>("shader")
			.addConstructor<void(*)(std::string, std::string)>()
			.addFunction("use", &shader::use)
			.addFunction("compile", &shader::compile)
			.addFunction("setfloat", &shader::setFloat)
			.addFunction("setint", &shader::setInt)
			.addFunction("setvec2", &shader::setVec2)
			.addFunction("adduniform", &shader::addUniform)
			.endClass();
	}
private:
	shader(shader& o) {}
	void operator=(shader s) {}
	std::map<std::string, int> uniforms;

	GLuint m_vs, m_fs, m_program;
	std::string loadShaderData(std::string filename);
	static int linecount(std::string t);
};

#endif //__IX_SHADER__