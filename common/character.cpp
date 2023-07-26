#include "character.h" 
Character::Character(int animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName)
{
	_animationSpeed = animSpeed;

	_spriteAmountW = spriteAmountW;
	_spriteAmountH = spriteAmountH;

	_fileName = fileName;

	_currentFrame = 0;

	float uvW = 1.0f / _spriteAmountW;
	float uvH = 1.0f / _spriteAmountH;
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
	float uvW = 1.0f / _spriteAmountW;
	float uvH = 1.0f / _spriteAmountH;

	this->sprite = new Sprite(_fileName, uvH, uvW);

	return _currentFrame; 
}

void Character::clearLastFrame()
{
	delete this->sprite;
	this->sprite = nullptr;
}