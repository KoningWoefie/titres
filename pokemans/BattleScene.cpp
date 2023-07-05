#include "BattleScene.h"

BattleScene::BattleScene() : Scene()
{
	player = new Trainer("player", 300, 150, 60, 35);
	jeffrey = new Trainer("jeffrey", 200, 300, 35, 60);

	hud = new HUD();

	player->AddBattler(new Battler("dumbass", 500, 300, 10, 10));

	srand(time(NULL));
	this->AddChild(hud);

	_selectedIndexX = 0;
	_selectedIndexY = 0;
	_selectedMenu = 0;
	hud->GetInteractableButtons()[_selectedMenu][_selectedIndexY][_selectedIndexX]->Select(true);
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
	if (hud->IsFighting())
	{
		_selectedMenu = 1;
		hud->GetInteractableButtons()[_selectedMenu][_selectedIndexY][_selectedIndexX]->Select(true);
	}
	else
	{
		_selectedMenu = 0;
		hud->GetInteractableButtons()[_selectedMenu][_selectedIndexY][_selectedIndexX]->Select(true);
	}
	selectButton();
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

int BattleScene::selectButton()
{
	int indexX = _selectedIndexX;
	int indexY = _selectedIndexY;
	if (input()->getKeyDown(Right))
	{
		indexX++;
		if (indexX >= hud->GetInteractableButtons()[_selectedIndexY].size())
		{
			return 0;
		}
	}
	if (input()->getKeyDown(Left))
	{
		indexX--;
		if (indexX < 0)
		{
			return 0;
		}
	}
	if (input()->getKeyDown(Up))
	{
		indexY--;
		if (indexY < 0)
		{
			return 0;
		}
	}
	if (input()->getKeyDown(Down))
	{
		indexY++;
		if (indexY >= hud->GetInteractableButtons().size())
		{
			return 0;
		}
	}
	if (indexX == _selectedIndexX && indexY == _selectedIndexY)
	{
		return 0;
	}
	hud->GetInteractableButtons()[_selectedMenu][_selectedIndexY][_selectedIndexX]->Select(false);
	hud->GetInteractableButtons()[_selectedMenu][indexY][indexX]->Select(true);
	_selectedIndexX = indexX;
	_selectedIndexY = indexY;
	return 1;
}