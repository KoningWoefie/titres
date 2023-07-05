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

	textBar = new Button();
	textBar->AddSprite("assets/TextBar.tga");

	fight->position = glm::vec3(896, 768, 0.0f);
	bag->position = glm::vec3(1152, 768, 0.0f);
	pokeman->position = glm::vec3(896, 896, 0.0f);
	run->position = glm::vec3(1152, 896, 0.0f);

	textBar->position = glm::vec3(384, 832, 0.0f);

	this->AddChild(fight);
	this->AddChild(bag);
	this->AddChild(pokeman);
	this->AddChild(run);

	interactableButtons.push_back(fight);
	interactableButtons.push_back(bag);
	interactableButtons.push_back(pokeman);
	interactableButtons.push_back(run);

	this->AddChild(textBar);
}
HUD::~HUD()
{
}

void HUD::update(float deltaTime)
{
}
