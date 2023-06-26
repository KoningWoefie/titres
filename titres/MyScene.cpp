#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	gridCreated = false;
	survivalButton = new Button();
	survivalButton->position = glm::vec3(500.0f, 360.0f, 0.0f);
	survivalButton->SetButtonText("Survival");
	survivalButton->SetCallbackFunction(std::bind(&MyScene::Survival, this));
	survivalButton->Select(true);

	timeAttackButton = new Button();
	timeAttackButton->position = glm::vec3(800.0f, 360.0f, 0.0f);
	timeAttackButton->SetButtonText("Time Attack");
	timeAttackButton->SetCallbackFunction(std::bind(&MyScene::TimeAttack, this));
	timeAttackButton->Select(false);

	buttons.push_back(survivalButton);
	buttons.push_back(timeAttackButton);

	this->AddChild(survivalButton);
	this->AddChild(timeAttackButton);
}

MyScene::~MyScene()
{
}

void MyScene::update(float deltaTime)
{
	if (!gridCreated)
	{
		selectButton();
		return;
	}
	buttons[0]->Select(false);
	buttons[1]->Select(false);
	if (grid->checkGameOver())
	{
		DeleteGrid();
		return;
	}
	points->Message("Points:\n" + std::to_string(grid->GetPoints()));
	level->Message("Level\n" + std::to_string(grid->GetLevel()));
	linesCleared->Message("Lines: " + std::to_string(grid->GetLinesCleared()));

	if (_nextIndex != grid->GetNextIndex())
	{
		_nextIndex = grid->GetNextIndex();
		this->RemoveChild(displayPiece);
		delete displayPiece;
		displayPiece = nullptr;
		displayPiece = new Piece(glm::vec3(902.5f, 230.0f, 0.0f), _nextIndex);
		this->AddChild(displayPiece);
	}
	if (grid->GetTimeLeft() != -1)
	{
		timer->Message(std::to_string(grid->GetTimeLeft()));
	}
}

void MyScene::TimeAttack()
{
	CreateGrid(true);
}

void MyScene::Survival()
{
	CreateGrid(false);
}

int MyScene::CreateGrid(bool timeAttack)
{
	grid = new Grid(10, 22, timeAttack);
	grid->position = glm::vec3(484.0f, 164.0f, 0.0f);
	background = new MyEntity();
	background->scale = glm::vec3(4.0f, 4.0f, 1.0f);
	background->position = glm::vec3(640.0f, 480.0f, 0.0f);
	t = new Timer();
	_nextIndex = grid->GetNextIndex();
	displayPiece = new Piece(glm::vec3(902.5f, 240.0f, 0.0f), _nextIndex);

	//initialize all text
	points = new Text();
	level = new Text();
	type = new Text();
	next = new Text();
	linesCleared = new Text();
	timer = new Text();

	points->position = glm::vec3(902.5f, 625.0f, 0.0f);
	points->scale = glm::vec3(0.5f, 0.5f, 1.0f);

	timer->position = glm::vec3(885.0f, 525.0f, 0.0f);
	timer->scale = glm::vec3(0.6f, 0.6f, 1.0f);

	next->position = glm::vec3(902.5f, 180.0f, 0.0f);
	next->scale = glm::vec3(0.5f, 0.5f, 1.0f);
	next->Message("Next:");

	level->position = glm::vec3(400.0f, 150.0f, 0.0f);
	level->scale = glm::vec3(0.8f, 0.8f, 1.0f);
	level->Message("Level");

	linesCleared->position = glm::vec3(650.0f, 135.0f, 0.0f);
	linesCleared->scale = glm::vec3(0.6f, 0.6f, 1.0f);

	this->AddChild(grid);

	this->AddChild(background);

	this->AddChild(displayPiece);

	this->AddChild(points);
	this->AddChild(next);
	this->AddChild(level);
	this->AddChild(linesCleared);
	this->AddChild(timer);

	gridCreated = true;
	return 1;
}

int MyScene::DeleteGrid()
{
	this->RemoveChild(grid);
	this->RemoveChild(background);
	this->RemoveChild(displayPiece);
	this->RemoveChild(points);
	this->RemoveChild(next);
	this->RemoveChild(level);
	this->RemoveChild(linesCleared);
	this->RemoveChild(timer);

	delete grid;
	grid = nullptr;

	delete background;
	background = nullptr;

	delete displayPiece;
	displayPiece = nullptr;

	delete points;
	points = nullptr;

	delete next;
	next = nullptr;

	delete level;
	level = nullptr;

	delete linesCleared;
	linesCleared = nullptr;

	delete timer;
	timer = nullptr;

	delete t;
	t = nullptr;

	_nextIndex = 0;

	gridCreated = false;
	return 1;
}

int MyScene::selectButton()
{
	int index = selectedIndex;
	if (input()->getKeyDown(Right))
	{
		index += 1;
	}
	if (input()->getKeyDown(Left))
	{
		index -= 1;
	}
	if (index >= buttons.size() || index < 0)
	{
		return -1;
	}
	if (index == selectedIndex)
	{
		return 0;
	}
	buttons[index]->Select(true);
	buttons[selectedIndex]->Select(false);

	selectedIndex = index;
	return 1;
}