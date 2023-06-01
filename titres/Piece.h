#ifndef PIECE_H 
#define PIECE_H

#include <common/entity.h>
#include "block.h"

class Piece : public Entity
{ 
public: 
    Piece(int i); 
    virtual ~Piece();

	virtual void update(float deltaTime);

	std::vector<Block*> Blocks() { return _blocks; };

	void rotatePiece();

	void rotateCW();
	void rotateCCW();

private:
	std::vector<Block*> _blocks;
	Block* _anchorBlock;

	void createPiece(int index);

	std::vector<std::vector<std::vector<int>>> _positions;

	int rotationSortOf;
}; 
#endif // Piece_H