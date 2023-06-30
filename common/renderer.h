#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/scene.h>
#include <common/camera.h>
#include <common/sprite.h>
#include <common/resourcemanager.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void renderScene(Scene* scene);
	void renderEntity(Entity* entity, glm::mat4 PaMa);
	void renderSprite(Sprite* sprite, glm::mat4 mm);
	void renderSpriteSheet(std::vector<Sprite*> spriteSheet, glm::mat4 mm);
	GLFWwindow* window() { return _window; };

	float updateDeltaTime();

private:
	int init();

	GLFWwindow* _window;

	GLuint loadShaders(
		const std::string& vertex_file_path,
		const std::string& fragment_file_path
	);

	GLuint _programID;

	Camera* _camera; // reference to scene->camera

	ResourceManager _resMan;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
};

#endif /* RENDERER_H */
