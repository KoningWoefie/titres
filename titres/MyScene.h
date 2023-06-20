#ifndef MYSCENE_H
#define MYSCENE_H

#include <common/scene.h>
#include <common/timer.h>
#include <common/text.h>
#include "Grid.h"
#include "Piece.h"
#include "MyEntity.h"
#include "Button.h"

class MyScene : public Scene
{
public:
	MyScene();

	virtual ~MyScene();

	virtual void update(float deltaTime);

private:

	void TimeAttack();
	void Survival();

	int CreateGrid(bool timeAttack);
	int DeleteGrid();
	int selectButton();

	bool gridCreated;


	MyEntity* background = nullptr;
	Grid* grid = nullptr;
	Piece* displayPiece = nullptr;
	Timer* t = nullptr;
	Text* level = nullptr;
	Text* points = nullptr;
	Text* type = nullptr;
	Text* next = nullptr;
	Text* linesCleared = nullptr;
	Text* timer = nullptr;

	Button* timeAttackButton;
	Button* survivalButton;

	std::vector<Button*> buttons;
	int _nextIndex = 0;
	int selectedIndex = 0;
};
#endif // !MYSCENE_H
