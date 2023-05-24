#include "MyEntity.h"

MyEntity::MyEntity()
{
	this->AddSprite("assets/kingkong.tga");
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	if (input()->getKey(Right))
	{
		this->position.x += deltaTime * 10; // for now, do it here
	}
	if (input()->getKeyDown(Left))
	{
		this->position.x -= deltaTime * 1000; // for now, do it here
	}
}