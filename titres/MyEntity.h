#ifndef MYENTITY_H
#define MYENTITY_H

#include <common/entity.h>

class MyEntity : public Entity
{
public:
	MyEntity();
	~MyEntity();

	virtual void update(float deltaTime);

private:

};
#endif // !MYENTITY_H
