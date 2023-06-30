#ifndef TEXT_H 
#define TEXT_H 

#include <common/entity.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Text : public Entity
{ 
public: 
    Text(); 
    virtual ~Text();

	virtual void update(float deltaTime);

	void ClearMessage();

	void Message(std::string m);

private:
	std::string _message;
}; 
#endif // text_H 
