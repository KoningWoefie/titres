#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>
#include "MyEntity.h"

class MyScene : public Scene
{
public:
	MyScene();

	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	MyEntity* kingkong;
};
#endif // !MYSCENE_H
