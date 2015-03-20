#include "..\include\mesh.h"

void Mesh::calculateNormals(std::vector<vertex>& vertices)
{
	for (int i = 0; i < vertices.size(); i += 3)
	{
		vec3 e1 = vertices[i + 1].getPosition() - vertices[i].getPosition();
		vec3 e2 = vertices[i + 2].getPosition() - vertices[i].getPosition();

		vec3 n = normalize(cross(e1, e2));

		vertices[i    ].setNormal(n);
		vertices[i + 1].setNormal(n);
		vertices[i + 2].setNormal(n);
	}
}

void Mesh::calculateTangents(std::vector<vertex>& vertices)
{
	for (int i = 0; i < vertices.size(); i += 3)
	{
		vec2 i0 = vertices[i    ].getTexCoord();
		vec2 i1 = vertices[i + 1].getTexCoord();
		vec2 i2 = vertices[i + 2].getTexCoord();

		vec3 e1 = vertices[i + 1].getPosition() - vertices[i].getPosition();
		vec3 e2 = vertices[i + 2].getPosition() - vertices[i].getPosition();

		float deltaU1 = i1.x - i0.x;
		float deltaU2 = i2.x - i0.x;
		float deltaV1 = i1.y - i0.y;
		float deltaV2 = i2.y - i0.y;

		float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
		float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

		vec3 tang = vec3(0.0f);

		tang.x = f * (deltaV2 * e1.x - deltaV1 * e2.x);
		tang.y = f * (deltaV2 * e1.y - deltaV1 * e2.y);
		tang.z = f * (deltaV2 * e1.z - deltaV1 * e2.z);

		vertices[i    ].setTangent(tang);
		vertices[i + 1].setTangent(tang);
		vertices[i + 2].setTangent(tang);
	}
}

void Mesh::addVertices(std::vector<vertex> vertices, std::vector<int> indices)
{
	size = vertices.size();
	isize = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

}

void Mesh::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vec3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, isize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}