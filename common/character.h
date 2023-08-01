#ifndef CHARACTER_H 
#define CHARACTER_H

#include "common/entity.h"

class Character : public Entity
{ 
public: 
    Character(float animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName); 
    virtual ~Character();

	virtual void update(float deltaTime);

	int Frame(int index);

	void clearLastFrame();

	void setAnimation(std::vector<int> anim) {	animations.push_back(anim);	};

private:

	int _currentFrame;

	int _animationSpeed;
	//how many sprites are in the width of the spritesheet
	int _spriteAmountW;
	//how many sprites are in the height of the spritesheet
	int _spriteAmountH;

	std::string _fileName;

	typedef std::vector<int> animation;
	std::vector<animation> animations;
}; 
#endif // character_H 