#include "BattleScene.h"

BattleScene::BattleScene() : Scene()
{
	player = new Trainer("player", 300, 150, 60, 35);
	jeffrey = new Trainer("jeffrey", 200, 300, 35, 60);

	player->AddBattler(new Battler("dumbass", 500, 300, 10, 10));

	srand(time(NULL));
} 
BattleScene::~BattleScene() 
{
	delete player;
	delete jeffrey;
	player = nullptr;
	jeffrey = nullptr;
}

void BattleScene::update(float deltaTime)
{
	if (player->GetHealth() <= 0 || jeffrey->GetHealth() <= 0)
	{
		return;
	}
	if (player->GetActiveBattler()->GetHealth() <= 0)
	{
		ChoosePokeman(0, player);
	}
	if (input()->getKeyDown(KEY_Z))
	{
		ChoosePokeman(1, player);
	}
	if (input()->getKeyDown(KEY_X))
	{
		Battle();
	}
}

int BattleScene::Battle()
{
	Battler* activeBat1 = player->GetActiveBattler();
	Battler* activeBat2 = jeffrey->GetActiveBattler();
	if (activeBat1->GetSpeed() == activeBat2->GetSpeed())
	{
		int random = rand() % 2;
		if (random == 0)
		{
			activeBat1->Attack(activeBat2);
			if (activeBat2->GetHealth() > 0)
			{
				activeBat2->Attack(activeBat1);
			}
		}
		else
		{
			activeBat2->Attack(activeBat1);
			if (activeBat1->GetHealth() > 0)
			{
				activeBat1->Attack(activeBat2);
			}
		}
	}
	else if (activeBat1->GetSpeed() > activeBat2->GetSpeed())
	{
		activeBat1->Attack(activeBat2);
		if (activeBat2->GetHealth() > 0)
		{
			activeBat2->Attack(activeBat1);
		}
	}
	else
	{
		activeBat2->Attack(activeBat1);
		if (activeBat1->GetHealth() > 0)
		{
			activeBat1->Attack(activeBat2);
		}
	}
	return 0;
}

int BattleScene::ChoosePokeman(int index, Trainer* t)
{
	t->SetActiveBattler(index);
	return 0;
}