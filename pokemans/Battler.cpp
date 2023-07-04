#include "Battler.h" 
Battler::Battler(std::string name) 
{
	_health = 100;
	_attack = 20;

	_name = name;
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
	if (_health <= 0)
	{
		return 0;
	}
	_health -= damage;
	return 1;
}
