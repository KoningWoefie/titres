#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>
#include <common/timer.h>
#include <common/text.h>
#include "Grid.h"
#include "Piece.h"
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
	Piece* displayPiece;
	Timer* t;
	Text* level;
	Text* points;
	Text* type;
	Text* next;
	Text* linesCleared;

	int _nextIndex;
};
#endif // !MYSCENE_H
