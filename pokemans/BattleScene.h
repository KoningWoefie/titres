#ifndef BATTLESCENE_H 
#define BATTLESCENE_H

#include <common/scene.h>

#include "Battler.h"

class BattleScene : public Scene
{ 
public: 
    BattleScene(); 
    virtual ~BattleScene();

	virtual void update(float deltaTime);

private:
	Battler* bat1;
	Battler* bat2;
}; 
#endif // BattleScene_H 
