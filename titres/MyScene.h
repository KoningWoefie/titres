#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>
#include <common/timer.h>
#include "Grid.h"
#include "MyEntity.h"

class MyScene : public Scene
{
public:
	MyScene();

	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	MyEntity* background;
	Grid* grid;
	Timer* t;
};
#endif // !MYSCENE_H
