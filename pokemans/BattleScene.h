#ifndef BATTLESCENE_H 
#define BATTLESCENE_H

#include <common/scene.h>

#include "pokemans/Trainer.h"
#include "pokemans/HUD.h"
#include "pokemans/MoveList.h"
#include "pokemans/Player.h"

class BattleScene : public Scene
{ 
public: 
    BattleScene(); 
    virtual ~BattleScene();

	virtual void update(float deltaTime);

private:
	void Battle();
	int ChoosePokeman(int index, Trainer* t);

	int selectButton();

	int _selectedIndexX;
	int _selectedIndexY;
	int _selectedMenu;
	Trainer* player;
	Trainer* jeffrey;
	HUD* hud;
}; 
#endif // BattleScene_H 
