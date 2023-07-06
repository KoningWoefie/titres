#ifndef MOVE_H 
#define MOVE_H 

#include <string>

class Move 
{ 
public: 
    Move(std::string name, int power, int accuracy, int attackType); 
    virtual ~Move();

	std::string GetName() { return _name; }
	int GetPower() { return _power; }
	int GetAccuracy() { return _accuracy; }
	int GetAttackType() { return _attackType; }
private:
	std::string _name;
	int _power;
	int _accuracy;
	int _attackType;
}; 
#endif // Move_H 
