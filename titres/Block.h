#ifndef BLOCK_H 
#define BLOCK_H

#include <common/entity.h>

class Block : public Entity
{ 
public: 
    Block(float x, float y); 
    virtual ~Block(); 

	virtual void update(float deltaTime);

	int getIndexX() { return _index_X; };
	void setIndexX(int newIndex) { _index_X = newIndex; };

	int getIndexY() { return _index_Y; };
	void setIndexY(int newIndex) { _index_Y = newIndex; };

	void setIndices(int newIndex_X, int newIndex_Y) { _index_X = newIndex_X; _index_Y = newIndex_Y; }

private:
	int _index_X;
	int _index_Y;
}; 
#endif // Block_H 
