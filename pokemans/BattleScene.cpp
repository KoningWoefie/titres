#include "BattleScene.h"

BattleScene::BattleScene() : Scene()
{
	bat1 = new Battler("barry");
	bat2 = new Battler("jeffrey");

	srand(time(NULL));
} 
BattleScene::~BattleScene() 
{
	delete bat1;
	delete bat2;
	bat1 = nullptr;
	bat2 = nullptr;
}

void BattleScene::update(float deltaTime)
{
	if (bat1->GetHealth() <= 0 || bat2->GetHealth() <= 0)
	{
		return;
	}
	if (bat1->GetSpeed() == bat2->GetSpeed())
	{
		int random = rand() % 2;
		if (random == 0)
		{
			bat1->Attack(bat2);
			if (bat2->GetHealth() > 0)
			{
				bat2->Attack(bat1);
			}
		}
		else
		{
			bat2->Attack(bat1);
			if (bat1->GetHealth() > 0)
			{
				bat1->Attack(bat2);
			}
		}
	}
	else if (bat1->GetSpeed() > bat2->GetSpeed())
	{
		bat1->Attack(bat2);
		if(bat2->GetHealth() > 0)
		{ 
			bat2->Attack(bat1);
		}
	}
	else
	{
		bat2->Attack(bat1);
		if (bat1->GetHealth() > 0)
		{
			bat1->Attack(bat2);
		}
	}
}