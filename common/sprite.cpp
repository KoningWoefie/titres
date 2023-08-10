#include <iostream>
#include <cstdio>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <common/sprite.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Sprite::Sprite(const std::string& imagepath)
{
	spriteSheet = false;
	// Transform
	spritePosition = glm::vec2(0.0f, 0.0f);
	spriteRotation = 0.0f;
	spriteScale = glm::vec2(1.0f, 1.0f);

	// these will be set correctly in loadTGA()
	_width = 0;
	_height = 0;

	_vertexbuffer = 0;
	_uvbuffer = 0;

	_uvOffset = glm::vec2(0.0f, 0.0f);

	_textureName = imagepath;
	setup = false;

	color = glm::vec3(255, 255, 255);

	pivot = glm::vec2(0.5f, 0.5f);

	SetUpUV(1,1);
}

Sprite::Sprite(const std::string& imagepath, float uvHeight, float uvWidth)
{
	spriteSheet = true;
	// Transform
	spritePosition = glm::vec2(0.0f, 0.0f);
	spriteRotation = 0.0f;
	spriteScale = glm::vec2(1.0f, 1.0f);

	// these will be set correctly in loadTGA()
	_width = 0;
	_height = 0;

	_vertexbuffer = 0;
	_uvbuffer = 0;

	_uvOffset = glm::vec2(0.0f, 0.0f);

	_textureName = imagepath;
	setup = false;

	color = glm::vec3(255, 255, 255);

	pivot = glm::vec2(0.5f, 0.5f);

	SetUpUV(uvHeight, uvWidth);
}

Sprite::Sprite(const std::string& imagepath, int width, int height, int t, int b, int l, int r)
{
	spriteSheet = false;
	pivot = glm::vec2(0.5f, 0.5f);
	_textureName = imagepath;
	_width = width;
	_height = height;

	spritePosition = glm::vec2(0.0f, 0.0f);
	spriteRotation = 0.0f;
	spriteScale = glm::vec2(1.0f, 1.0f);

	_uvOffset = glm::vec2(0.0f, 0.0f);

	setup = false;

	color = glm::vec3(255, 255, 255);

	float uvX = 0;
	float uvY = 0;

	float offsetX = 0;
	float offsetY = 0;

	//middle
	uvX = (width - (l + r)) / width;
	uvY = (height - (t + b)) / height;
	offsetX = l / width;
	offsetY = b / height;
	Mesh* S1 = new Mesh((width - (l + r)), (height - (t + b)), uvX, uvY, pivot, glm::vec2(offsetX, offsetY), false);
	meshes.push_back(S1);

	//left
	uvX = l / width;
	uvY = (height - (t + b)) / height;
	offsetX = 0;
	offsetY = t / height;
	Mesh* SY1 = new Mesh(l, (height - (t + b)), uvX, uvY, pivot, glm::vec2(offsetX, offsetY), false, 1);
	meshes.push_back(SY1);

	//right
	uvX = r / width;
	uvY = (height - (t + b)) / height;
	offsetX = (width - r) / width;
	offsetY = t / height;
	Mesh* SY2 = new Mesh(width, (height - (t + b)), uvX, uvY, pivot, glm::vec2(offsetX, offsetY), false, 1);
	meshes.push_back(SY2);

	//top
	uvX = (width - (l + r)) / width;
	uvY = t / height;
	offsetX = l / width;
	offsetY = 0;
	Mesh* SX1 = new Mesh((width - (l + r)), t, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), false, 2);
	meshes.push_back(SX1);

	//bottom
	uvX = (width - (l + r)) / width;
	uvY = b / height;
	offsetX = l / width;
	offsetY = (height - b) / height;
	Mesh* SX2 = new Mesh((width - (l + r)), b, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), false, 2);
	meshes.push_back(SX2);

	//top left corner
	uvX = l / width;
	uvY = t / height;
	offsetX = 0;
	offsetY = 0;
	Mesh* C1 = new Mesh(l, t, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), true);
	meshes.push_back(C1);

	//top right corner
	uvX = r / width;
	offsetX = (width - r) / width;
	offsetY = 0;
	Mesh* C2 = new Mesh(r, t, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), true);
	meshes.push_back(C2);

	//bottom left corner
	uvX = l / width;
	uvY = b / height;
	offsetX = 0;
	offsetY = (height - b) / height;
	Mesh* C3 = new Mesh(l, b, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), true);
	meshes.push_back(C3);

	//bottom right corner
	uvX = r / width;
	offsetX = (width - r) / width;
	Mesh* C4 = new Mesh(r, b, uvX, uvY, pivot, glm::vec2(offsetX, offsetY), true);
	meshes.push_back(C4);
}

Sprite::~Sprite()
{
}

void Sprite::ClearTextures()
{
	glDeleteTextures(1, &_texture); // texture created in loadTGA() with glGenTextures()
}

void Sprite::SetUpUV(float uvHeight, float uvWidth)
{
	_uv = glm::vec2(uvWidth, uvHeight);
}

void Sprite::SetUpSize(float width, float height, GLuint texture)
{
	_width = width;
	_height = height;
	spriteSize.x = width;
	spriteSize.y = height;

	_texture = texture;
}

void Sprite::Index(int i)
{
	int w = 1.0f / _uv[0];
	int h = 1.0f / _uv[1];

	if (i >= w * h || i < 0) { std::cout << "You fucking moron" << std::endl; return; };

	int xPos = i % w;
	int yPos = i / w;

	_uvOffset[0] = xPos * _uv[0];
	_uvOffset[1] = yPos * _uv[1];

	_index = i;
	//std::cout << _index << std::endl;
}

GLuint Sprite::loadTGA(const std::string& imagepath)
{
	std::cout << "Loading TGA: " << _textureName << std::endl;

	// Open the file on disk
	FILE *file;

	file = fopen(imagepath.c_str(), "rb");

	if (!file) {
		std::cout << "error: unable to open file" << std::endl;
		return 0;
	}

	// Read header (width, height, type, bitdepth)
	unsigned char type[4];
	unsigned char info[6];
	if (!fread (&type, sizeof (char), 3, file)) return 0;
	fseek (file, 12, SEEK_SET);
	if (!fread (&info, sizeof (char), 6, file)) return 0;

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		std::cout << "error: image type neither color or grayscale" << std::endl;
		fclose(file);
		return 0;
	}

	// Set width, height, bitdepth
	_width = info[0] + info[1] * 256;
	_height = info[2] + info[3] * 256;
	unsigned char bitdepth = info[4] / 8;

	if (bitdepth != 1 && bitdepth != 3 && bitdepth != 4) {
		std::cout << "bitdepth not 1, 3 or 4" << std::endl;
		fclose(file);
		return 0;
	}

	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_width & (_width - 1)) != 0) {
		std::cout << "warning: " << _textureName << "’s width is not a power of 2" << std::endl;
	}
	if ((_height & (_height - 1)) != 0) {
		std::cout << "warning: " << _textureName << "’s height is not a power of 2" << std::endl;
	}
	if (_width != _height) {
		std::cout << "warning: " << _textureName << " is not square" << std::endl;
	}

	// Calculate pixelbuffer size in bytes
	unsigned int imagesize = _width * _height * bitdepth;

	// Create a buffer
	unsigned char* data = new unsigned char [imagesize];

	// Read the actual data from the file into the buffer
	if (!fread(data, 1, imagesize, file)) return 0;

	// Everything is in memory now, close the file
	fclose(file);

	// Create one OpenGL texture
	// Be sure to also delete it from where you called this with glDeleteTextures()
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// filter the Texture
	unsigned char filter = 1;
	switch (filter) {
		case 0:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case 1:
			// Linear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case 2:
			// Bilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		case 3:
			// Trilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		default:
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
	}

	// wrapping
	// GL_REPEAT, GL_MIRRORED_REPEAT or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// handle transparency and grayscale and give the image to OpenGL
	switch (bitdepth) {
		case 4:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
			break;
		case 1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, _width, _height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
			break;
		default:
			std::cout << "error: bitdepth not 4, 3, or 1" << std::endl;
			break;
	}

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	spriteSize.x = _width;
	spriteSize.y = _height;

	// createBuffer(_uvs);

	// Return the ID of the texture we just created
	_texture = textureID;
	return textureID;
}