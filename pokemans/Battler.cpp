#include "Battler.h" 
Battler::Battler(std::string name, int health, int attack, int defense, int speed) : Entity()
{
	_name = name;

	_health = health;
	_attack = attack;
	_defense = defense;
	_speed = speed;

	_activeMove = 0;
} 
Battler::~Battler() 
{ 
}

void Battler::update(float deltaTime)
{

}

int Battler::Attack(Battler* enemy)
{
	std::cout << _name << " is now attacking: " << enemy->GetName() << "with the move " << _moves[_activeMove]->GetName() << std::endl;
	enemy->TakeDamage((_moves[_activeMove]->GetPower()*_attack)/20);
	std::cout << "health of " << enemy->GetName() << " is now: " << enemy->GetHealth() << std::endl;
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

int Battler::LearnMove(int index)
{
	_moves.push_back(moveList->GetMove(index));
	return 1;
}
