#ifndef HUD_H 
#define HUD_H 

#include <common/entity.h>
#include "Button.h"

class HUD : public Entity
{ 
public: 
    HUD(); 
    virtual ~HUD();

	virtual void update(float deltaTime);

private:
	Button* fight;
	Button* bag;
	Button* pokeman;
	Button* run;

	Button* textBar;

	std::vector<Button*> interactableButtons;
}; 
#endif // HUD_H 
