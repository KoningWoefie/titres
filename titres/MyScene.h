#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>

class MyScene : public Scene
{
public:
	MyScene();

	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	Sprite* rgba;
};
#endif // !MYSCENE_H
