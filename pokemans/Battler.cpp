#include "Battler.h" 
Battler::Battler(std::string name, int health, int attack, int defense, int speed)
{
	_name = name;

	_health = health;
	_attack = attack;
	_defense = defense;
	_speed = speed;
} 
Battler::~Battler() 
{ 
}

void Battler::update(float deltaTime)
{

}

int Battler::Attack(Battler* enemy)
{
	std::cout << "attacking: " << enemy->GetName() << std::endl;
	enemy->TakeDamage(_attack);
	std::cout << "health of enemy now: " << enemy->GetHealth() << std::endl;
	return 1;
}

int Battler::TakeDamage(int damage)
{
	_health -= damage/_defense;
	if (_health <= 0)
	{
		_health = 0;
		std::cout << _name << " is now resting in peace" << std::endl;
		return 0;
	}
	return 1;
}
