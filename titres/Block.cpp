#include "Block.h" 
Block::Block(float x, float y) 
{
	this->AddSprite("assets/EmptyBlock.tga");
	this->position = glm::vec3(x, y, 0);

	_occupied = false;

	indices[0] = { -1 };
	indices[1] = { -1 };

	_index_X = 0;
	_index_Y = 0;
} 
Block::~Block() 
{ 
}

void Block::update(float deltaTime)
{

}

void Block::updatePos(glm::vec3 newPos)
{
	this->position = newPos;
}
