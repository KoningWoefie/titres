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
	void setIndexX(int newIndex) { _index_X = newIndex; actuallySetIndices(); };

	int getIndexY() { return _index_Y; };
	void setIndexY(int newIndex) { _index_Y = newIndex; actuallySetIndices(); };

	int* getIndices() { return indices; };

	void setIndices(int newIndex_X, int newIndex_Y) { _index_X = newIndex_X; _index_Y = newIndex_Y; actuallySetIndices(); }
	void setIndicesSortOf(int newIndex_X, int newIndex_Y) { _index_X += newIndex_X; _index_Y += newIndex_Y; actuallySetIndices(); }

	void actuallySetIndices() { indices[0] = _index_X; indices[1] = _index_Y; };

	void updatePos(glm::vec3 newPos);

	bool getOccupied() { return _occupied; };
	void setOccupied(bool o) { _occupied = o; };

private:
	int _index_X;
	int _index_Y;

	bool _occupied;

	int indices[2];
}; 
#endif // Block_H 
