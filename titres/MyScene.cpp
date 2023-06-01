#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	grid = new Grid(10, 10);
	kingkong = new MyEntity();
	t = new Timer();
	this->AddChild(t);
	t->StartTimer();

	kingkong->position = glm::vec3(400.0f, 300.0f, 0.0f);

	this->AddChild(kingkong);
	this->AddChild(grid);
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	std::cout << t->Seconds() << std::endl;
}