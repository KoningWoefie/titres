#include "MoveList.h"

MoveList::MoveList() 
{
	Move* bdyslm = new Move("BodySlam", 85, 100, 0);
	Move* kick = new Move("Kick", 95, 100, 0);
	Move* bchslp = new Move("BitchSlap", 35, 100, 0);
	Move* bite = new Move("Bite", 60, 100, 0);
	Move* scratch = new Move("Scratch", 40, 100, 0);
	Move* punch = new Move("Punch", 80, 100, 0);
	Move* tackle = new Move("Tackle", 40, 100, 0);
	Move* sweep = new Move("Sweep", 45, 100, 0);

	moves.push_back(bdyslm);
	moves.push_back(kick);
	moves.push_back(bchslp);
	moves.push_back(bite);
	moves.push_back(scratch);
	moves.push_back(punch);
	moves.push_back(tackle);
	moves.push_back(sweep);
}

MoveList::~MoveList() 
{
}

MoveList* MoveList::moveList()
{
	if (MoveList::_moveList == nullptr)
	{
		_moveList = new MoveList();
	}
	return _moveList;
}

Move* MoveList::GetMove(int index)
{
	if (index >= moves.size() || index < 0) { return nullptr; }
	return moves[index];
}

MoveList* MoveList::_moveList = nullptr;