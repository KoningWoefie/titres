#ifndef GRID_H 
#define GRID_H 

#include <common/entity.h>
#include <common/timer.h>
#include "Block.h"
#include "Piece.h"

class Grid : public Entity
{ 
public: 
    Grid(int gridSizeX, int gridSizeY, bool timeAttack);
    virtual ~Grid();

	virtual void update(float deltaTime);

	std::vector<std::vector<Block*>> grid;

	void SetFallingBlock(Piece* fb) { _fallingBlock = fb; };

	void makeFallingPiece(int i);

	void rotateFallingPiece();

	void fallFallingPiece();

	void removeFallingPiece();

	bool checkGameOver();

	void clearLine();

	void clearGrid();

	void LevelUp();

	int GetPoints() { return _points; }
	int GetNextIndex() { return nextPieceIndex; }
	int GetLevel() { return _currentLevel; }
	int GetLinesCleared() { return _currentLinesCleared; }

	int GetTimeLeft();

	int calculateEndPoint();

	int instaDrop();

private:
	void moveBlock();
	void GivePoints(int linesCleared);

	Piece* _fallingBlock;
	Timer* t;
	Timer* inputDelay;
	Timer* timeAttackTimer;

	std::vector<std::vector<Block*>> _fallenBlocks;

	int _gridSizeX;
	int _gridSizeY;

	int _endIndices[4];

	int requiredLines;

	int _currentLevel;
	int _currentLinesCleared;
	int _points;
	int nextPieceIndex;

	float _fallTime;
	float _inputDelay;

	bool _pieceLanded;
	bool _gameOver;
	bool _timeAttack;
}; 
#endif // Grid_H 
