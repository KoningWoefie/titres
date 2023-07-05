#include "Button.h" 
Button::Button() 
{
	buttonText = new Text();
	buttonText->position = glm::vec3(0.0f, 0.0f, 0.0f);
	buttonText->scale = glm::vec3(0.6f, 0.6f, 1.0f);
	_selected = false;

	this->AddSprite("assets/button.tga");
	this->AddChild(buttonText);
} 
Button::~Button() 
{ 
	delete buttonText;
	buttonText = nullptr;
}

void Button::update(float deltaTime)
{
	if (!_selected)
	{
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		return;
	}
	this->scale = glm::vec3(1.1f, 1.1f, 1.0f);
	if (input()->getKeyDown(KEY_X))
	{
		_CallbackFunction();
	}
}