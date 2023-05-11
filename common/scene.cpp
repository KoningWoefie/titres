#include <iostream>
#include <common/scene.h>
#include <common/config.h>

Scene::Scene() : Entity()
{
	_camera = new Camera();
}

Scene::~Scene()
{
	// Delete all the sprites
	for (size_t i = 0; i < children.size(); i++)
	{
		delete children[i];
		children[i] = nullptr;
	}
	children.clear();

	// Delete camera
	delete _camera;
}
