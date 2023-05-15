#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Sprite
{
public:
	Sprite(const std::string& imagepath);
	virtual ~Sprite();

	GLuint getTexture() { return _texture; };
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	unsigned int width() { return _width; };
	unsigned int height() { return _height; };

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

	std::string TextureName() { return _textureName; };

	GLuint loadTGA(const std::string& imagepath);
	void createBuffer();
	void SetUp(GLuint vb, GLuint uv, GLuint texture, unsigned int width, unsigned int height);

private:

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	unsigned int _width;
	unsigned int _height;

	bool setup;

	std::string _textureName;
};

#endif /* SPRITE_H */
