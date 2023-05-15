#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>
#include "Grid.h"
#include "MyEntity.h"

class MyScene : public Scene
{
public:
	MyScene();

	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	MyEntity* kingkong;
	Grid* grid;
};
#endif // !MYSCENE_H
