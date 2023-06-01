#ifndef GRID_H 
#define GRID_H 

#include <common/entity.h>
#include <common/timer.h>
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

	void fallFallingPiece();

	void removeFallingPiece();

private:
	void moveBlock();

	Piece* _fallingBlock;
	Timer* t;

	int _gridSizeX;
	int _gridSizeY;

	bool _pieceLanded;
}; 
#endif // Grid_H 
