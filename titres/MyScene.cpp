#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	/*Sprite* kingkong = new Sprite("assets/kingkong.tga");
	kingkong->position = glm::vec3(400.0f, 300.0f, 0.0f);
	Sprite* pencils = new Sprite("assets/pencils.tga");
	Sprite* pencils2 = new Sprite("assets/pencils.tga");
	pencils->position = glm::vec3(900.0f, 300.0f, 0.0f);
	rgba = new Sprite("assets/rgba.tga");
	rgba->position = glm::vec3(WIDTH / 2, HEIGHT / 2, 0.0f);
	rgba->scale = glm::vec3(3.0f, 3.0f, 1.0f);*/

	kingkong = new MyEntity();

	kingkong->position = glm::vec3(400.0f, 300.0f, 0.0f);

	this->AddChild(kingkong);
	/*this->AddChild(pencils);
	this->AddChild(pencils2);
	this->AddChild(rgba);*/
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	kingkong->position.x += deltaTime * 10; // for now, do it here
}