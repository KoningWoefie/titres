#include "character.h"

Character::Character(float animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName)
{
	_animationSpeed = animSpeed;

	_spriteAmountW = spriteAmountW;
	_spriteAmountH = spriteAmountH;

	_fileName = fileName;

	_currentFrame = 0;

	float uvW = 1.0f / _spriteAmountW;
	float uvH = 1.0f / _spriteAmountH;

	this->Frame(_currentFrame);
} 
Character::~Character() 
{
}

void Character::update(float deltaTime)
{

}

int Character::Frame(int index) 
{
	this->clearLastFrame();
	_currentFrame = index;
	float uvW = 1.0f/_spriteAmountW;
	float uvH = 1.0f/_spriteAmountH;

	Sprite* s = new Sprite(_fileName, uvH, uvW);
	s->Index(index);
	// std::cout << this->sprite->GetUV().x << ", " << this->sprite->GetUV().y << std::endl;
	this->spriteSheet.push_back(s);

	s = nullptr;
	
	return _currentFrame; 
}

void Character::clearLastFrame()
{
	this->spriteSheet.clear();
	delete this->sprite;
	this->sprite = nullptr;
}