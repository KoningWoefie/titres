#include "Grid.h" 
#include "sstream"
#include "fstream"

Grid::Grid(int gridSizeX, int gridSizeY) 
{
	_gridSizeX = gridSizeX - 1;
	_gridSizeY = gridSizeY - 1;

	_fallTime = 0.6f;

	_pieceLanded = false;
	_gameOver = false;

	t = new Timer();
	inputDelay = new Timer();
	this->AddChild(t);
	this->AddChild(inputDelay);
	t->TogglePause();
	inputDelay->StartTimer();
	srand(time(NULL));

	for (int y = 0; y < gridSizeY; y++)
	{
		std::vector<Block*> emptyRow;
		std::vector<Block*> row;
		for (int x = 0; x < gridSizeX; x++)
		{
			Block* b = new Block(x * 32 + 16, y * 32 - 48);
			b->setIndices(x, y);
			row.push_back(b);
			Block* b2 = nullptr;
			emptyRow.push_back(b2);
			this->AddChild(b);
		}
		grid.push_back(row);
		_fallenBlocks.push_back(emptyRow);
	}

	this->makeFallingPiece(rand()%7);
}
Grid::~Grid() 
{
}

void Grid::checkGameOver()
{
	for (Block* b : grid[1])
	{
		if (b->getOccupied())
		{
			_gameOver = true;
		}
	}
}

void Grid::clearLine()
{
	bool lineCleared = false;
	int linesCleared = 0;
	int index = 0;
	for (int i = grid.size() - 1; i >= 0; i--)
	{
		bool no = false;
		for (Block* b : _fallenBlocks[i])
		{
			if (b == nullptr)
			{
				no = true;
			}
		}

		if (!no)
		{
			for (int j = grid[i].size() - 1; j >= 0; j--)
			{
				grid[i][j]->setOccupied(false);
				this->RemoveChild(_fallenBlocks[i][j]);
				delete _fallenBlocks[i][j];
				_fallenBlocks[i][j] = nullptr;
				index = i;
			}
			lineCleared = true;
			linesCleared++;
		}
	}
	if (lineCleared)
	{
		for (int i = index; i >= 0; i--)
		{
			for (int j = grid[i].size() - 1; j >= 0; j--)
			{
				if (_fallenBlocks[i][j] != nullptr)
				{
					grid[i][j]->setOccupied(false);
					_fallenBlocks[i][j]->setIndexY(_fallenBlocks[i][j]->getIndexY() + linesCleared);
					grid[i + linesCleared][j]->setOccupied(true);
					_fallenBlocks[i][j]->updatePos(grid[i + linesCleared][j]->position);
					_fallenBlocks[i + linesCleared][j] = _fallenBlocks[i][j];
					_fallenBlocks[i][j] = nullptr;
				}
			}
		}
	}
}

void Grid::clearGrid()
{
	for (int i = _fallenBlocks.size() - 1; i >= 0; i--)
	{
		for (int j = _fallenBlocks[i].size() - 1; j >= 0; j--)
		{
			this->RemoveChild(_fallenBlocks[i][j]);
			delete _fallenBlocks[i][j];
			_fallenBlocks[i][j] = nullptr;;
		}
	}
	for (std::vector<Block*> g : grid)
	{
		for (Block* b : g)
		{
			b->setOccupied(false);
		}
	}
	_gameOver = false;
}

void Grid::moveBlock()
{
	int indices[4] = {-1,-1,-1,-1};
	if (input()->getKeyDown(Left) || (input()->getKey(Left) && inputDelay->Seconds() >= 0.2f ))
	{
		for (int i = 0; i < 4; i++)
		{
			int indexX = _fallingBlock->Blocks()[i]->getIndexX();
			int indexY = _fallingBlock->Blocks()[i]->getIndexY();
			if (indexX == 0 || grid[indexY][indexX - 1]->getOccupied())
			{
				return;
			}
			indexX--;
			indices[i] = indexX;
		}
	}
	if (input()->getKeyDown(Right) || (input()->getKey(Right) && inputDelay->Seconds() >= 0.2f))
	{
		for (int i = 0; i < 4; i++)
		{
			int indexX = _fallingBlock->Blocks()[i]->getIndexX();
			int indexY = _fallingBlock->Blocks()[i]->getIndexY();
			if (indexX == _gridSizeX || grid[indexY][indexX + 1]->getOccupied())
			{
				return;
			}
			indexX++;
			indices[i] = indexX;
		}
	}
	if (indices[0] != -1)
	{
		for (int i = 0; i < 4; i++)
		{
			_fallingBlock->Blocks()[i]->updatePos(grid[_fallingBlock->Blocks()[i]->getIndexY()][indices[i]]->position);
			_fallingBlock->Blocks()[i]->setIndexX(indices[i]);
			inputDelay->StartTimer();
		}
	}
}

void Grid::makeFallingPiece(int i)
{
	_fallingBlock = new Piece(i);
	for (int i = 0; i < 4; i++)
	{
		_fallingBlock->Blocks()[i]->updatePos(grid[_fallingBlock->Blocks()[i]->getIndexY()][_fallingBlock->Blocks()[i]->getIndexX()]->position);
	}
	this->AddChild(_fallingBlock);
}

void Grid::rotateFallingPiece()
{
	if (input()->getKeyDown(KEY_Z))
	{
		_fallingBlock->rotateCW();
		bool canTurn = true;
		int indicesList[4][2] = { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} };
		for (int i = 0; i < 4; i++)
		{
			int indices[2] = { _fallingBlock->Blocks()[i]->getIndices()[0], _fallingBlock->Blocks()[i]->getIndices()[1] };
			if ((indices[0] < 0 || indices[0] > _gridSizeX) || (indices[1] < 0 || indices[1] > _gridSizeY) || (grid[indices[1]][indices[0]]->getOccupied()))
			{
				_fallingBlock->rotateCCW();
				canTurn = false;
				return;
			}
			indicesList[i][0] = indices[0];
			indicesList[i][1] = indices[1];
		}
		if (canTurn)
		{
			for (int i = 0; i < 4; i++)
			{
				_fallingBlock->Blocks()[i]->updatePos(grid[indicesList[i][1]][indicesList[i][0]]->position);
			}
		}
	}
	if (input()->getKeyDown(KEY_X))
	{
		_fallingBlock->rotateCCW();
		bool canTurn = true;
		int indicesList[4][2] = { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} };
		for (int i = 0; i < 4; i++)
		{
			int indices[2] = { _fallingBlock->Blocks()[i]->getIndices()[0], _fallingBlock->Blocks()[i]->getIndices()[1] };
			if ((indices[0] < 0 || indices[0] > _gridSizeX) || (indices[1] < 0 || indices[1] > _gridSizeY) || (grid[indices[1]][indices[0]]->getOccupied()))
			{
				_fallingBlock->rotateCW();
				canTurn = false;
				return;
			}
			indicesList[i][0] = indices[0];
			indicesList[i][1] = indices[1];
		}
		if (canTurn)
		{
			for (int i = 0; i < 4; i++)
			{
				_fallingBlock->Blocks()[i]->updatePos(grid[indicesList[i][1]][indicesList[i][0]]->position);
			}
		}
	}
}

void Grid::update(float deltaTime)
{
	if (_gameOver)
	{
		if (input()->getKeyDown(Enter))
		{
			clearGrid();
		}
		return;
	}
	moveBlock();
	rotateFallingPiece();
	fallFallingPiece();
	removeFallingPiece();
	checkGameOver();
}

void Grid::fallFallingPiece()
{
	float fallTime = 0.6f;
	if (input()->getKey(Down))
	{
		fallTime = _fallTime / 16;
	}
	int indices[4] = {-1,-1,-1,-1};
	if (t->Seconds() > fallTime)
	{
		for (int i = 0; i < 4; i++)
		{
			int indexY = _fallingBlock->Blocks()[i]->getIndexY();
			int indexX = _fallingBlock->Blocks()[i]->getIndexX();
			if (indexY == _gridSizeY || grid[indexY + 1][indexX]->getOccupied())
			{
				_pieceLanded = true;
				return;
			}
			indexY++;
			indices[i] = indexY;
		}
		t->StartTimer();
	}
	if (indices[0] != -1)
	{
		for (int i = 0; i < 4; i++)
		{
			_fallingBlock->Blocks()[i]->updatePos(grid[indices[i]][_fallingBlock->Blocks()[i]->getIndexX()]->position);
			_fallingBlock->Blocks()[i]->setIndexY(indices[i]);
		}
	}
}

void Grid::removeFallingPiece()
{
	if (_pieceLanded)
	{
		for (int i = 0; i < 4; i++)
		{
			this->AddChild(_fallingBlock->Blocks()[i]);
			_fallenBlocks[_fallingBlock->Blocks()[i]->getIndexY()][_fallingBlock->Blocks()[i]->getIndexX()] = _fallingBlock->Blocks()[i];
			grid[_fallingBlock->Blocks()[i]->getIndexY()][_fallingBlock->Blocks()[i]->getIndexX()]->setOccupied(true);
			_fallingBlock->RemoveChild(_fallingBlock->Blocks()[i]);
		}

		clearLine();

		this->RemoveChild(_fallingBlock);
		delete _fallingBlock;
		_fallingBlock = nullptr;
		_pieceLanded = false;
		makeFallingPiece(rand()%7);
	}
}
