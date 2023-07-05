#include "Trainer.h" 
Trainer::Trainer(std::string name, int health, int attack, int defense, int speed) : Battler(name, health, attack, defense, speed)
{
	activeBattler = this;
	party.push_back(this);
} 
Trainer::~Trainer() 
{
	for (int i = 1; i < party.size(); i++)
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
		std::cout << "Party is not that big moron" << std::endl;
		return 0;
	}
	activeBattler = party[index];
	return 1;
}
