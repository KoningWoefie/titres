#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <common/entity.h>
#include <common/camera.h>
#include <common/sprite.h>
#include <common/config.h>

class Scene : public Entity
{
public:
	Scene();
	virtual ~Scene();

	virtual void update(float deltaTime) = 0;

	Camera* camera() { return _camera; };

private:
	Camera* _camera;
};

#endif /* SCENE_H */
