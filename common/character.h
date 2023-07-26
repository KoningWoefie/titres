#ifndef CHARACTER_H 
#define CHARACTER_H

#include "common/entity.h"

class Character : public Entity
{ 
public: 
    Character(int animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName); 
    virtual ~Character();

	virtual void update(float deltaTime);

	int Frame(int index);

	void clearLastFrame();
private:

	int _currentFrame;

	int _animationSpeed;
	//how many sprites are in the width of the spritesheet
	int _spriteAmountW;
	//how many sprites are in the height of the spritesheet
	int _spriteAmountH;

	std::string _fileName;
}; 
#endif // character_H 
