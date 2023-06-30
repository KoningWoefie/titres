#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <common/sprite.h>
#include <common/config.h>
#include <glm/glm.hpp>
#include <common/inputmanager.h>
#include <common/sh2dconfig.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(float deltaTime) = 0;

	void AddChild(Entity* e);

	void RemoveChild(Entity* e);

	InputManager* input() { return _input; };

	void AddSprite(const std::string& fileName);
	void AddSpriteSheet(const std::string& fileName, float uvHeight, float uvWidth);
	std::vector<Sprite*> GetSpriteSheet() { return spriteSheet; }

	std::vector<Entity*> Children() { return children; };
	Sprite* ESprite() { return sprite; }

	Entity* parent;

	glm::vec3 position;
	glm::vec3 scale;
	float rotation;

protected:
	std::vector<Entity*> children;
	std::vector<Sprite*> spriteSheet;
	Sprite* sprite;

private:
	InputManager* _input = InputManager::input();
};
#endif // !ENTITY_H
