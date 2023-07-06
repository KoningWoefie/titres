#include "Move.h" 
Move::Move(std::string name, int power, int accuracy, int attackType)
{
	_name = name;
	_power = power;
	_accuracy = accuracy;
	_attackType = attackType;
}
Move::~Move() 
{ 
}
