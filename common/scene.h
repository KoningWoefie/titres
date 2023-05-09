#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <common/camera.h>
#include <common/sprite.h>
#include <common/config.h>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void update(float deltaTime) = 0;

	void addSprite(Sprite* sprite);

	Camera* camera() { return _camera; };
	std::vector<Sprite*>& sprites() { return _sprites; };

private:
	Camera* _camera;
	std::vector<Sprite*> _sprites;
};

#endif /* SCENE_H */
