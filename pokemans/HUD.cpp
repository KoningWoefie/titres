#include "HUD.h" 
HUD::HUD() : Entity()
{
	fight = new Button();
	fight->AddSprite("assets/FightButton.tga");
	bag = new Button();
	bag->AddSprite("assets/BagButton.tga");
	pokeman = new Button();
	pokeman->AddSprite("assets/PokemanButton.tga");
	run = new Button();
	run->AddSprite("assets/RunButton.tga");

	move1 = new Button();
	move2 = new Button();
	move3 = new Button();
	move4 = new Button();

	textBar = new Button();
	textBar->AddSprite("assets/TextBar.tga");

	fight->position = glm::vec3(896, 768, 0.0f);
	bag->position = glm::vec3(1152, 768, 0.0f);
	pokeman->position = glm::vec3(896, 896, 0.0f);
	run->position = glm::vec3(1152, 896, 0.0f);

	move1->position = glm::vec3(896, 768, 0.0f);
	move2->position = glm::vec3(1152, 768, 0.0f);
	move3->position = glm::vec3(896, 896, 0.0f);
	move4->position = glm::vec3(1152, 896, 0.0f);

	textBar->position = glm::vec3(384, 832, 0.0f);

	fight->SetCallbackFunction(std::bind(&HUD::ShowFightMenu, this));

	this->AddChild(fight);
	this->AddChild(bag);
	this->AddChild(pokeman);
	this->AddChild(run);

	for (int i = 0; i < 2; i++)
	{
		InteractableButtonsX row;
		interactableMenuButtons.push_back(row);
	}

	interactableMenuButtons[0].push_back(fight);
	interactableMenuButtons[0].push_back(bag);
	interactableMenuButtons[1].push_back(pokeman);
	interactableMenuButtons[1].push_back(run);

	for (int i = 0; i < 4; i++)
	{
		InteractableButtonsX row;
		interactableFightButtons.push_back(row);
	}

	interactableFightButtons[0].push_back(move1);
	interactableFightButtons[0].push_back(move2);
	interactableFightButtons[1].push_back(move3);
	interactableFightButtons[1].push_back(move4);

	interactableButtons.push_back(interactableMenuButtons);
	interactableButtons.push_back(interactableFightButtons);

	this->AddChild(textBar);
	_fightMenu = false;
}
HUD::~HUD()
{
}

void HUD::update(float deltaTime)
{
}

int HUD::ShowFightMenu()
{
	this->RemoveChild(fight);
	this->RemoveChild(bag);
	this->RemoveChild(pokeman);
	this->RemoveChild(run);

	this->AddChild(move1);
	this->AddChild(move2);
	this->AddChild(move3);
	this->AddChild(move4);
	_fightMenu = true;
	return 1;
}

int HUD::ShowMenu()
{
	this->RemoveChild(move1);
	this->RemoveChild(move2);
	this->RemoveChild(move3);
	this->RemoveChild(move4);

	this->AddChild(fight);
	this->AddChild(bag);
	this->AddChild(pokeman);
	this->AddChild(run);
	_fightMenu = false;
	return 1;
}
