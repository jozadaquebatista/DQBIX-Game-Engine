#include "..\include\mesh.h"

void mesh::addVertices(std::vector<vertex> vertices)
{
	size = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
}

void mesh::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vec3));

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}