#include "MyScene.h"

MyScene::MyScene() : Scene()
{

	kingkong = new MyEntity();

	kingkong->position = glm::vec3(400.0f, 300.0f, 0.0f);

	this->AddChild(kingkong);
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	kingkong->position.x += deltaTime * 10; // for now, do it here
}