#include "character.h"

Character::Character(float animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName)
{
	_animationSpeed = animSpeed;

	_spriteAmountW = spriteAmountW;
	_spriteAmountH = spriteAmountH;

	_fileName = fileName;

	_currentFrame = 0;
	_frame = 0;

	float uvW = 1.0f / _spriteAmountW;
	float uvH = 1.0f / _spriteAmountH;

	this->Frame(_currentFrame);

	_timer = new Timer();
} 
Character::~Character() 
{
	delete _timer;
	_timer = nullptr;
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
	for (int i = 0; i < spriteSheet.size(); i++)
	{
		delete spriteSheet[i];
		spriteSheet[i] = nullptr;
	}
	
	this->spriteSheet.clear();
}

int Character::PlayAnimation(int index)
{
    if(_timer->Seconds() >= _animationSpeed)
    {
    	if(_frame >= animations[index].size())
    	{
    	    _frame = 0;
    	    this->Frame(animations[index][_frame]);
    	    _timer->StopTimer();
			// std::cout << "Animation finished" << std::endl;
			return 1;
    	}
		// std::cout << "Animation playing" << std::endl;
    	this->Frame(animations[index][_frame]);
		std::cout << animations[index][_frame] << std::endl;
    	_frame++;
		_timer->StopTimer();
    	_timer->StartTimer();
    }
	return 0;
}