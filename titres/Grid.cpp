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
			Block* b = new Block(x * 32 + 16, y * 32 + 16);
			b->setIndices(x, y);
			row.push_back(b);
			this->AddChild(b);
		}
		grid.push_back(row);
	}

	this->makeFallingPiece(2);
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
			if (indexX == 0)
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
			if (indexX == _gridSizeX)
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
		_fallingBlock->rotatePiece();
		for (int i = 0; i < 4; i++)
		{
			_fallingBlock->Blocks()[i]->updatePos(grid[_fallingBlock->Blocks()[i]->getIndexY()][_fallingBlock->Blocks()[i]->getIndexX()]->position);
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
			if (indexY == _gridSizeY)
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
			_fallingBlock->RemoveChild(_fallingBlock->Blocks()[i]);
		}

		this->RemoveChild(_fallingBlock);
		delete _fallingBlock;
		_fallingBlock = nullptr;
		_pieceLanded = false;
		makeFallingPiece(1);
	}
}
