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

	void checkGameOver();

	void clearLine();

	void clearGrid();

private:
	void moveBlock();

	Piece* _fallingBlock;
	Timer* t;

	std::vector<std::vector<Block*>> _fallenBlocks;

	int _gridSizeX;
	int _gridSizeY;

	float _fallTime;

	bool _pieceLanded;
	bool _gameOver;
}; 
#endif // Grid_H 
