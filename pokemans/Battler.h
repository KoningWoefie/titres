#ifndef BATTLER_H 
#define BATTLER_H

#include <common/entity.h>
#include <functional>

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

	int LearnMove(std::function<void()> move);
	//int ForgetMove(); //to do

	std::vector<std::function<void()>> GetMoves() { return moves; }

private:
	int _health;
	int _attack;
	int _defense;
	int _speed;
	//int _specialAttack;
	//int _specialDefense;

	std::string _name;
	std::vector<std::function<void()>> moves;
}; 
#endif // Battler_H 
