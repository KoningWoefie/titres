#ifndef PIECE_H 
#define PIECE_H

#include <common/entity.h>
#include "block.h"

class Piece : public Entity
{ 
public: 
    Piece(int i); 
	Piece(glm::vec3 pos, int i);
    virtual ~Piece();

	virtual void update(float deltaTime);

	std::vector<Block*> Blocks() { return _blocks; };

	void rotateCW();
	void rotateCCW();

	void ClearBlocks() { _blocks.clear(); }

private:

	void createPiece(int index);

	typedef std::vector<int> indices;
	typedef std::vector<indices> blocks;

	std::vector<blocks> _positions;
	std::vector<Block*> _blocks;

	int rotationSortOf;
}; 
#endif // Piece_H