#include <common/entity.h>

Entity::Entity()
{
	parent = nullptr;
	sprite = nullptr;
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = 0;
}

Entity::~Entity()
{
	parent = nullptr;
	if (spriteSheet.size() > 0)
	{
		for (int i = spriteSheet.size() - 1; i >= 0; i--)
		{
			delete spriteSheet[i];
			spriteSheet[i] = nullptr;
		}
	}
	delete sprite;
	sprite = nullptr;
}

void Entity::AddChild(Entity* e)
{
	children.push_back(e);
	e->parent = this;
}

void Entity::RemoveChild(Entity* e)
{
	for (int i = children.size() - 1; i >= 0; i--)
	{
		if (children[i] == e)
		{
			children.erase(children.begin() + i);
			return;
		}
	}
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

void Entity::AddSpriteSheet(const std::string& fileName, float uvHeight, float uvWidth)
{
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
	sprite = new Sprite(fileName, uvHeight, uvWidth);
}