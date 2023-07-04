#include "Trainer.h" 
Trainer::Trainer(std::string name, int health, int attack, int defense, int speed) : Battler(name, health, attack, defense, speed)
{
	activeBattler = this;
} 
Trainer::~Trainer() 
{
	for (int i = 0; i < party.size(); i++)
	{
		delete  party[i];
		party[i] = nullptr;
	}activeBattler = nullptr;
}

void Trainer::update(float deltaTime)
{
}

int Trainer::AddBattler(Battler* battler)
{
	party.push_back(battler);
	return 1;
}

int Trainer::SetActiveBattler(int index)
{
	if (index < 0 || index >= party.size())
	{
		return 0;
	}
	activeBattler = party[index];
	return 1;
}
