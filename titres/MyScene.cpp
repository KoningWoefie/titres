#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	grid = new Grid(10, 22, true);
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

	level->position = glm::vec3(350.0f, 150.0f, 0.0f);
	level->scale = glm::vec3(0.8f, 0.8f, 1.0f);
	level->Message("Level");

	linesCleared->position = glm::vec3(620.0f, 135.0f, 0.0f);
	linesCleared->scale = glm::vec3(0.6f, 0.6f, 1.0f);

	this->AddChild(grid);

	this->AddChild(background);

	this->AddChild(displayPiece);

	this->AddChild(points);
	this->AddChild(next);
	this->AddChild(level);
	this->AddChild(linesCleared);
	this->AddChild(timer);
}

MyScene::~MyScene()
{
}

void MyScene::update(float deltaTime)
{
	points->Message("Points:|" + std::to_string(grid->GetPoints()));
	level->Message("Level|" + std::to_string(grid->GetLevel()));
	linesCleared->Message("Lines: " + std::to_string(grid->GetLinesCleared()));
	timer->Message(std::to_string(grid->GetTimeLeft()));
	if (_nextIndex != grid->GetNextIndex())
	{
		_nextIndex = grid->GetNextIndex();
		this->RemoveChild(displayPiece);
		delete displayPiece;
		displayPiece = nullptr;
		displayPiece = new Piece(glm::vec3(902.5f, 230.0f, 0.0f), _nextIndex);
		this->AddChild(displayPiece);
	}
}