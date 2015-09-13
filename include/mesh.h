#ifndef __IX_MESH__
#define __IX_MESH__
#pragma once

#include "graphics.h"
#include "vertex.h"
#include <vector>

class Mesh
{
public:
	Mesh()
	{
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);
	}

    ~Mesh()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
    }

	void addVertices(vector<vertex> vertices, vector<int> indices);
	void draw(int mode);

	static void calculateNormals(vector<vertex>& vertices);
	static void calculateTangents(vector<vertex>& vertices);

private:
	GLuint vbo, ibo;
	int size, isize;
};

#endif //__IX_MESH__
