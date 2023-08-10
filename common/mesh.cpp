#include <common/mesh.h>

Mesh::Mesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot)
{
	std::vector<glm::vec3> vertices;

    //first triangle
    vertices.push_back(glm::vec3(width - (pivot.x * width), -pivot.y * height, 0.0f));
	vertices.push_back(glm::vec3(-pivot.x * width, -pivot.y * height, 0.0f));
	vertices.push_back(glm::vec3(-pivot.x * width,  height - (pivot.y * height), 0.0f));
	// second triangle
	vertices.push_back(glm::vec3(-pivot.x * width,  height - (pivot.y * height), 0.0f));
	vertices.push_back(glm::vec3(width - (pivot.x * width), height - (pivot.y * height), 0.0f));
	vertices.push_back(glm::vec3(width - (pivot.x * width), -pivot.y * height, 0.0f));

    _uvs.push_back(glm::vec2(uvWidth, uvHeight));
	_uvs.push_back(glm::vec2(0.0f, uvHeight));
	_uvs.push_back(glm::vec2(0.0f, 0.0f));

	_uvs.push_back(glm::vec2(0.0f, 0.0f));
	_uvs.push_back(glm::vec2(uvWidth, 0.0f));
	_uvs.push_back(glm::vec2(uvWidth, uvHeight));

    generateBuffers(vertices, _uvs);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_vertexbuffer);
    glDeleteBuffers(1, &_uvbuffer);
}

int Mesh::generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv)
{
    glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	// Send UV's to GPU
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
}