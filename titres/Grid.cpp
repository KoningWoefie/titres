#include "Grid.h" 

Grid::Grid(int gridSizeX, int gridSizeY) 
{
	_gridSizeX = gridSizeX - 1;
	_gridSizeY = gridSizeY - 1;

	_pieceLanded = false;

	t = new Timer();
	this->AddChild(t);
	t->TogglePause();

	for (int y = 0; y < gridSizeY; y++)
	{
		std::vector<Block*> row;
		for (int x = 0; x < gridSizeX; x++)
		{
			Block* b = new Block(x * 32 + 16, y * 32 - 48);
			b->setIndices(x, y);
			row.push_back(b);
			this->AddChild(b);
		}
		grid.push_back(row);
	}

	this->makeFallingPiece(1);
}
Grid::~Grid() 
{
}

void Grid::moveBlock()
{
	int indices[4] = {-1,-1,-1,-1};
	if (input()->getKeyDown(Left))
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
	if (input()->getKeyDown(Right))
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
			if ((indices[0] < 0 || indices[0] > _gridSizeX) || (indices[1] < 0 || indices[1] > _gridSizeY))
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
	moveBlock();
	rotateFallingPiece();
	fallFallingPiece();
	removeFallingPiece();
}

void Grid::fallFallingPiece()
{
	int indices[4] = {-1,-1,-1,-1};
	if (t->Seconds() > 0.6f)
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
			grid[_fallingBlock->Blocks()[i]->getIndexY()][_fallingBlock->Blocks()[i]->getIndexX()]->setOccupied(true);
			_fallingBlock->RemoveChild(_fallingBlock->Blocks()[i]);
		}

		this->RemoveChild(_fallingBlock);
		delete _fallingBlock;
		_fallingBlock = nullptr;
		_pieceLanded = false;
		makeFallingPiece(1);
	}
}
