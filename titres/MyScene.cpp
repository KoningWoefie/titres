#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	grid = new Grid(10, 22);
	grid->position = glm::vec3(484.0f, 164.0f, 0.0f);
	background = new MyEntity();
	background->scale = glm::vec3(4.0f, 4.0f, 1.0f);
	background->position = glm::vec3(640.0f, 480.0f, 0.0f);
	t = new Timer();
	//text = new Text();
	//text->position = glm::vec3(WIDTH/2, HEIGHT/2, 0.0f);
	//text->Message("Hello world");

	this->AddChild(grid);

	this->AddChild(background);

	//this->AddChild(text);
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	//std::cout << t->Seconds() << std::endl;
}