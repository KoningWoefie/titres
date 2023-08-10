#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <common/mesh.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Sprite
{
public:
	Sprite(const std::string& imagepath);
	Sprite(const std::string& imagepath, int width, int height, int t, int b, int l, int r);
	Sprite(const std::string& imagepath, float uvHeight, float uvWidth);

	virtual ~Sprite();
	void ClearTextures();

	GLuint getTexture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };
	glm::vec2 GetUV() { return _uv; }

	unsigned int width() { return _width; };
	unsigned int height() { return _height; };

	glm::vec2 getUVOffset() { return _uvOffset; };

	glm::vec2 spritePosition;
	float spriteRotation;
	glm::vec2 spriteScale;
	glm::vec2 spriteSize;
	glm::vec2 pivot;

	glm::vec3 color;

	std::string TextureName() { return _textureName; };

	std::vector<Mesh*> Meshes() {	return meshes;	};

	GLuint loadTGA(const std::string& imagepath);
	void createBuffer(std::vector<glm::vec2> uv);
	void SetUpUV(float uvHeight, float uvWidth);

	void SetUpSize(float width, float height, GLuint texture);

	void Index(int index);

private:

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	std::vector<glm::vec2> _uvs;
	glm::vec2 _uv;
	glm::vec2 _uvOffset;

	unsigned int _width;
	unsigned int _height;

	int _index;

	bool setup;
	bool spriteSheet;

	std::string _textureName;

	std::vector<Mesh*> meshes;
};

#endif /* SPRITE_H */
