#ifndef GRID_H 
#define GRID_H 

#include <common/entity.h>
#include "Block.h"

class Grid : public Entity
{ 
public: 
    Grid(int gridSizeX, int gridSizeY); 
    virtual ~Grid(); 

	virtual void update(float deltaTime);

	std::vector<std::vector<Block*>> grid;

	void SetFallingBlock(Block* fb) { _fallingBlock = fb; };

private:
	void moveBlock();

	Block* _fallingBlock;

	int _gridSizeX;
	int _gridSizeY;
}; 
#endif // Grid_H 
