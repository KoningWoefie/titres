#include <common/entity.h>

Entity::Entity()
{
	parent = nullptr;
	sprite = nullptr;
	position = glm::vec3(0,0,0);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = 0;
}

Entity::~Entity()
{
	parent = nullptr;
}

void Entity::AddChild(Entity* e)
{
	children.push_back(e);
}

void Entity::AddSprite(const std::string& fileName)
{
	if(sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
	sprite = new Sprite(fileName);
}