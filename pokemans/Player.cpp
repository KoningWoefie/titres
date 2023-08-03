#include "Player.h"

Player::Player(float animSpeed, int spriteAmountW, int spriteAmountH, std::string fileName) : Character(animSpeed, spriteAmountW, spriteAmountH, fileName)
{
    playAnim = false;
    _selectedAnimation = 0;
    // animations.push_back( {0, 4, 8, 12} );
    setAnimation( {0, 4, 8, 12, 0, 4, 8, 12} );
    // animations.push_back( {1, 5, 9, 13} );
    setAnimation( {1, 5, 9, 13, 1, 5, 9, 13} );
    // animations.push_back( {2, 6, 10, 14} );
    setAnimation( {2, 6, 10, 14, 2, 6, 10, 14} );
    // animations.push_back( {3, 7, 11, 15} );
    setAnimation( {3, 7, 11, 15, 3, 7, 11, 15} );
}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
    if(playAnim)
    {
        int i = PlayAnimation(_selectedAnimation);
        if(i == 1)
        {
            playAnim = false;
        }
        return;
    }
    if(input()->getKeyDown(Up))
    {
        playAnim = true;
        _selectedAnimation = 0;
    }
    else if(input()->getKeyDown(Down))
    {
        playAnim = true;
        _selectedAnimation = 3;
    }
    else if(input()->getKeyDown(Left))
    {
        playAnim = true;
        _selectedAnimation = 1;
    }
    else if(input()->getKeyDown(Right))
    {
        playAnim = true;
        _selectedAnimation = 2;
    }
}