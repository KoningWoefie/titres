#ifndef BATTLESCENE_H 
#define BATTLESCENE_H

#include <common/scene.h>

#include "Trainer.h"

class BattleScene : public Scene
{ 
public: 
    BattleScene(); 
    virtual ~BattleScene();

	virtual void update(float deltaTime);

private:
	Trainer* bat1;
	Trainer* bat2;
}; 
#endif // BattleScene_H 
