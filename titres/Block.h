#ifndef BLOCK_H 
#define BLOCK_H

#include <common/entity.h>

class Block : public Entity
{ 
public: 
    Block(float x, float y); 
    virtual ~Block(); 

	virtual void update(float deltaTime);
}; 
#endif // Block_H 
