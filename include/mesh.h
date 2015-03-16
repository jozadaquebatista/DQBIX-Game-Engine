#ifndef __IX_MESH__
#define __IX_MESH__
#pragma once

#include "graphics.h"
#include "vertex.h"
#include <vector>

class mesh
{
public:
	mesh()
	{
		glGenBuffers(1, &vbo);
	}

	void addVertices(std::vector<vertex> vertices);
	void draw();

private:
	GLuint vbo;
	int size;
};

#endif //__IX_MESH__