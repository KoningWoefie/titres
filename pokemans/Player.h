#ifndef PLAYER_H
#define PLAYER_H

#include <common/character.h>

class Player : public Character
{
public:
    Player(float animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName);
    virtual ~Player();

    virtual void update(float deltaTime);
private:
    bool playAnim;
    int _selectedAnimation;
};

#endif