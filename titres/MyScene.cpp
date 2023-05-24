#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	grid = new Grid(10, 10);
	kingkong = new MyEntity();
	Block* block = new Block(100, 100);

	kingkong->position = glm::vec3(400.0f, 300.0f, 0.0f);

	this->AddChild(kingkong);
	this->AddChild(grid);
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	//kingkong->position.x += deltaTime * 10; // for now, do it here
}