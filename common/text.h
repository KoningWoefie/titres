#ifndef TEXT_H 
#define TEXT_H 

#include <common/entity.h>
class Text : public Entity
{ 
public: 
    Text(); 
    virtual ~Text();

	virtual void update(float deltaTime);

	void Message(std::string m);

private:
	std::string _message;
}; 
#endif // text_H 
