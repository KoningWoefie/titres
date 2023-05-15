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

private:
}; 
#endif // Grid_H 
