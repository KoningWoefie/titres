#ifndef BUTTON_H 
#define BUTTON_H

#include <common/entity.h>
#include <common/text.h>

#include <functional>

class Button : public Entity
{ 
public: 
    Button(); 
    virtual ~Button(); 

	virtual void update(float deltaTime);

	void SetCallbackFunction(std::function<void()> cbf) { _CallbackFunction = cbf; };

	void SetButtonText(std::string text)
	{
		buttonText->Message(text);
	}

	void Select(bool selected) { _selected = selected; }

private:
	std::function<void()> _CallbackFunction;

	bool _selected;

	Text* buttonText;
}; 
#endif // Button_H 
