#ifndef GRID_H 
#define GRID_H 

#include <common/entity.h>
#include "Block.h"
#include "Piece.h"

class Grid : public Entity
{ 
public: 
    Grid(int gridSizeX, int gridSizeY); 
    virtual ~Grid(); 

	virtual void update(float deltaTime);

	std::vector<std::vector<Block*>> grid;

	void SetFallingBlock(Piece* fb) { _fallingBlock = fb; };

	void makeFallingPiece(int i);

	void rotateFallingPiece();

private:
	void moveBlock();

	Piece* _fallingBlock;

	int _gridSizeX;
	int _gridSizeY;
}; 
#endif // Grid_H 
