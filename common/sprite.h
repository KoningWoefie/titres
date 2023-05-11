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
	void setTexture(GLuint texture) { _texture = texture; }
	GLuint vertexbuffer() { return _vertexbuffer; };
	GLuint uvbuffer() { return _uvbuffer; };

	unsigned int width() { return _width; };
	unsigned int height() { return _height; };

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

	std::string TextureName() { return _textureName; };

	GLuint loadTGA();

private:

	void createBuffer();

	GLuint _texture;
	GLuint _vertexbuffer;
	GLuint _uvbuffer;

	unsigned int _width;
	unsigned int _height;

	std::string _textureName;
};

#endif /* SPRITE_H */
