#include "Block.h" 
Block::Block(float x, float y) 
{
	this->AddSprite("assets/EmptyBlock.tga");
	this->position = glm::vec3(x, y, 0);
} 
Block::~Block() 
{ 
}

void Block::update(float deltaTime)
{

}
