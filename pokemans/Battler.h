#ifndef BATTLER_H 
#define BATTLER_H

#include <common/entity.h>

class Battler : public Entity
{ 
public: 
    Battler(std::string name, int health,int attack, int defense, int speed); 
    virtual ~Battler();

	virtual void update(float deltaTime);

	int Attack(Battler* enemy);

	int TakeDamage(int damage);

	std::string GetName() { return _name; }
	int GetHealth() { return _health; }
	int GetSpeed() { return _speed; }

private:
	int _health;
	int _attack;
	int _defense;
	int _speed;
	//int _specialAttack;
	//int _specialDefense;

	std::string _name;
}; 
#endif // Battler_H 
