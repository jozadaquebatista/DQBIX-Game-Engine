#include "shader.h"


void shader::addUniform(std::string name)
{
	int uloc = glGetUniformLocation(m_program, name.c_str());
	if (uloc == -1)
	{
		printf("Could not find uniform '%s'.\n", name);
		exit(EXIT_FAILURE);
	}
	uniforms[name] = uloc;
}

void shader::updateUniforms(Matrix4 model, Matrix4 view_proj)
{
	Matrix4 view;
	view.identity();

	setMatrix("mvp", (view_proj * view * model).invert());
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

	std::string vss = loadShaderData(fs);
	const GLchar* v[1];
	v[0] = vss.c_str();
	GLint vlengths[1];
	vlengths[0] = vss.size();

	m_vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vs, 1, new GLchar* const[] { (GLchar*)vss.c_str() }, (int*)vss.size());
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

	std::string fss = loadShaderData(fs);
	const GLchar* f[1];
	f[0] = fss.c_str();
	GLint flengths[1];
	flengths[0] = vss.size();

	m_fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fs, 1, new GLchar* const[] { (GLchar*)fss.c_str() }, (int*)fss.size());
	glCompileShader(m_fs);

	glGetShaderiv(m_fs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar log[1024];
		glGetShaderInfoLog(m_fs, 1024, NULL, log);
		fprintf(stderr, "Fragment Shader Error:\n%s", log);
		exit(EXIT_FAILURE);
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vs);
	glAttachShader(m_program, m_fs);

	compile();

	addUniform("mvp");
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
		printf("Could not find uniform '%s'.\n", name);
	}
}

void shader::setInt(std::string name, int val)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniform1i(pos->second, val);
	}
	else
	{
		printf("Could not find uniform '%s'.\n", name);
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
		printf("Could not find uniform '%s'.\n", name);
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
		printf("Could not find uniform '%s'.\n", name);
	}
}

void shader::setMatrix(std::string name, Matrix4 mat)
{
	std::map<std::string, int>::const_iterator pos = uniforms.find(name);
	if (pos != uniforms.end())
	{
		glUniformMatrix4fv(pos->second, 16, true, mat.get());
	}
	else
	{
		printf("Could not find uniform '%s'.\n", name);
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
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i] == '\n')
		{
			count++;
		}
	}
	return count;
}
