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

private:
	std::vector<Block*> _blocks;

	void createPiece(int index);
}; 
#endif // Piece_H