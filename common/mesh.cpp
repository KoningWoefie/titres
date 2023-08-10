#include <common/mesh.h>

Mesh::Mesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot)
{
    _width = width;
    _height = height;
    _uvWidth = uvWidth;
    _uvHeight = uvHeight;
    _pivot = pivot;

    _uvOffset = glm::vec2(0.0f, 0.0f);
    _corner = false;
    nineSlice = false;
    _type = 0;
    meshPos = glm::vec2(0.0f, 0.0f);

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

Mesh::Mesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot, glm::vec2 uvOffset, bool corner, int type)
{
    _width = width;
    _height = height;
    _uvWidth = uvWidth;
    _uvHeight = uvHeight;
    _pivot = pivot;
    _corner = corner;
    _uvOffset = uvOffset;
    _type = type;

    nineSlice = true;

    float x = (_uvOffset.x * width) + ((uvWidth * width) / 2);
    float y = (_uvOffset.y * height) + ((uvHeight * height) / 2);
    meshPos = glm::vec2(x, y);
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