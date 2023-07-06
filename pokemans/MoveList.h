#ifndef MOVELIST_H 
#define MOVELIST_H

#include <vector>
#include "pokemans/Move.h"

enum class Moves
{
	BodySlam = 0,
	Kick = 1,
	BitchSlap = 2,
	Bite = 3,
	Scratch = 4,
	Punch = 5,
	Tackle = 6,
	Sweep = 7
};

class MoveList 
{ 
public: 
	static MoveList* moveList();
    virtual ~MoveList();

	Move* GetMove(int index);
private:
	MoveList();
	static MoveList* _moveList;
	std::vector<Move*> moves;
}; 
#endif // MoveList_H 
