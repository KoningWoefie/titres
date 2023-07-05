#ifndef TRAINER_H 
#define TRAINER_H 

#include "Battler.h"

class Trainer : public Battler
{ 
public: 
    Trainer(std::string name, int health, int attack, int defense, int speed);
    virtual ~Trainer();

	virtual void update(float deltaTime);

	int AddBattler(Battler* battler);

	int SetActiveBattler(int index);

	Battler* GetActiveBattler() { return activeBattler; }

private:
	std::vector<Battler*> party;
	Battler* activeBattler;
}; 
#endif // Trainer_H 
