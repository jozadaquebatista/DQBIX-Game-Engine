#include "../include/shader.h"


void shader::addUniform(std::string name)
{
	int uloc = glGetUniformLocation(m_program, name.c_str());
	if (uloc == -1)
	{
		printf("Could not find uniform: %s\n", name.c_str());
	}
	uniforms.insert({ name, uloc });
}


void shader::addCommonUniforms()
{
	addUniform("proj");
	addUniform("model");
}

shader::~shader()
{
	if (m_vs) glDeleteShader(m_vs);
	if (m_fs) glDeleteShader(m_fs);
	if (m_program) glDeleteProgram(m_program);
}

shader* shader::fromString(std::string vs, std::string fs)
{
	m_program = glCreateProgram();
	if (vs != "")
	{
		const GLchar* v[1];
		v[0] = vs.c_str();
		GLint vlengths[1];
		vlengths[0] = vs.size();

		m_vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vs, 1, v, vlengths);
		glCompileShader(m_vs);

		GLint status;
		glGetShaderiv(m_vs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			GLchar log[1024];
			glGetShaderInfoLog(m_vs, 1024, NULL, log);
			fprintf(stderr, "Vertex Shader Error:\n%s", log);
			exit(EXIT_FAILURE);
		}
		glAttachShader(m_program, m_vs);
	}

	if (fs != "")
	{
		const GLchar* f[1];
		f[0] = fs.c_str();
		GLint flengths[1];
		flengths[0] = fs.size();

		m_fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fs, 1, f, flengths);
		glCompileShader(m_fs);

		GLint status;
		glGetShaderiv(m_fs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			GLchar log[1024];
			glGetShaderInfoLog(m_fs, 1024, NULL, log);
			fprintf(stderr, "Fragment Shader Error:\n%s", log);
			exit(EXIT_FAILURE);
		}
		glAttachShader(m_program, m_fs);
	}
	if (vs == "" && fs == "") return NULL;

	compile();

	return this;
}

shader::shader(std::string vs /*= ""*/, std::string fs /*= ""*/)
{
	if (vs == "" || fs == "") return;
	m_program = glCreateProgram();
	if (vs != "")
	{
		std::string vss = loadShaderData(vs);
		const GLchar* v[1];
		v[0] = vss.c_str();
		GLint vlengths[1];
		vlengths[0] = vss.size();

		m_vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vs, 1, v, vlengths);
		glCompileShader(m_vs);

		GLint status;
		glGetShaderiv(m_vs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			GLchar log[1024];
			glGetShaderInfoLog(m_vs, 1024, NULL, log);
			fprintf(stderr, "Vertex Shader Error:\n%s", log);
			exit(EXIT_FAILURE);
		}
		glAttachShader(m_program, m_vs);
	}

	if (fs != "")
	{
		std::string fss = loadShaderData(fs);
		const GLchar* f[1];
		f[0] = fss.c_str();
		GLint flengths[1];
		flengths[0] = fss.size();

		m_fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fs, 1, f, flengths);
		glCompileShader(m_fs);

		GLint status;
		glGetShaderiv(m_fs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			GLchar log[1024];
			glGetShaderInfoLog(m_fs, 1024, NULL, log);
			fprintf(stderr, "Fragment Shader Error:\n%s", log);
			exit(EXIT_FAILURE);
		}
		glAttachShader(m_program, m_fs);
	}
	
	compile();
}

void shader::use()
{
	glUseProgram(m_program);
}

void shader::compile()
{
	GLint status;	

	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);

	if (!status)
	{
		GLchar log[1024];
		glGetProgramInfoLog(m_program, 1024, NULL, log);
		fprintf(stderr, "Program Error:\n%s", log);
		exit(EXIT_FAILURE);
	}

	glValidateProgram(m_program);

	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
	if (!status)
	{
		GLchar log[1024];
		glGetShaderInfoLog(m_program, 1024, NULL, log);
		printf("Shader Error:\n%s", log);
		exit(EXIT_FAILURE);
	}
}

void shader::setFloat(std::string name, float val)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform1f(pos->second, val);
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

void shader::setInt(std::string name, int val)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform1iv(pos->second, 1, &val);
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

void shader::setVec2(std::string name, float x, float y)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform2f(pos->second, x, y);
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

void shader::setVec3(std::string name, float x, float y, float z)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform3f(pos->second, x, y, z);
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

void shader::setVec4(std::string name, float x, float y, float z, float w)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform4f(pos->second, x, y, z, w);
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

void shader::setMatrix(std::string name, mat4 mat)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniformMatrix4fv(pos->second, 1, false, value_ptr(mat));		
	}
	else
	{
		printf("Could not find uniform: %s.\n", name.c_str());
	}
}

std::string shader::loadShaderData(std::string filename)
{
	std::ifstream t(filename);
	std::string str((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());
	return str;
}

int shader::linecount(std::string t)
{
	int count = 0;
	for (unsigned int i = 0; i < t.size(); i++)
	{
		if (t[i] == '\n')
		{
			count++;
		}
	}
	return count;
}
