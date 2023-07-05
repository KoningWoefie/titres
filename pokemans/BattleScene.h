#ifndef BATTLESCENE_H 
#define BATTLESCENE_H

#include <common/scene.h>

#include "Trainer.h"
#include "HUD.h"

class BattleScene : public Scene
{ 
public: 
    BattleScene(); 
    virtual ~BattleScene();

	virtual void update(float deltaTime);

private:
	int Battle();
	int ChoosePokeman(int index, Trainer* t);
	Trainer* player;
	Trainer* jeffrey;
	HUD* hud;
}; 
#endif // BattleScene_H 
