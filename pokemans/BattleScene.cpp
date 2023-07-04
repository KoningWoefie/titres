#include "BattleScene.h" 
BattleScene::BattleScene() : Scene()
{
	bat1 = new Battler("barry");
	bat2 = new Battler("jeffrey");
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
	if (input()->getKeyDown(KEY_A))
	{
		bat1->Attack(bat2);
	}
	if (input()->getKeyDown(KEY_D))
	{
		bat2->Attack(bat1);
	}
}
