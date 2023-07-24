#ifndef HUD_H 
#define HUD_H 

#include <common/entity.h>
#include "Button.h"

class HUD : public Entity
{ 
public: 
	typedef std::vector<Button*> InteractableButtonsX;
	typedef std::vector<InteractableButtonsX> InteractableButtons;

    HUD(); 
    virtual ~HUD();

	virtual void update(float deltaTime);

	std::vector<InteractableButtons> GetInteractableButtons() { return interactableButtons; }

	bool IsFighting() { return _fightMenu; }

	int SetMoves(std::function<void()> callbackfunction);

	int ShowMenu();
private:
	int ShowFightMenu();

	Button* fight;
	Button* bag;
	Button* pokeman;
	Button* run;

	Button* move1;
	Button* move2;
	Button* move3;
	Button* move4;

	Button* textBar;

	std::vector<InteractableButtonsX> interactableMenuButtons;
	std::vector<InteractableButtonsX> interactableFightButtons;

	std::vector<InteractableButtons> interactableButtons;

	bool _fightMenu;
}; 
#endif // HUD_H 
