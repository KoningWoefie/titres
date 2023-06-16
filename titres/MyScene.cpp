#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	grid = new Grid(10, 22);
	grid->position = glm::vec3(484.0f, 164.0f, 0.0f);
	background = new MyEntity();
	background->scale = glm::vec3(4.0f, 4.0f, 1.0f);
	background->position = glm::vec3(640.0f, 480.0f, 0.0f);
	t = new Timer();
	_nextIndex = grid->GetNextIndex();
	displayPiece = new Piece(glm::vec3(902.5f, 230.0f, 0.0f), _nextIndex);

	//initialize all text
	points = new Text();
	level = new Text();
	type = new Text();
	next = new Text();
	linesCleared = new Text();

	points->position = glm::vec3(902.5f, 525.0f, 0.0f);
	points->scale = glm::vec3(0.5f, 0.5f, 1.0f);

	this->AddChild(grid);

	this->AddChild(background);

	this->AddChild(displayPiece);

	this->AddChild(points);
}

MyScene::~MyScene()
{
}

void MyScene::update(float deltaTime)
{
	points->Message(std::to_string(grid->GetPoints()));
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