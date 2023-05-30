#include "Grid.h" 

Grid::Grid(int gridSizeX, int gridSizeY) 
{
	_gridSizeX = gridSizeX - 1;
	_gridSizeY = gridSizeY - 1;

	_fallingBlock = new Piece(0);

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

	this->AddChild(_fallingBlock);
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
			indexX -= 1;
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
			indexX += 1;
			indices[i] = indexX;
		}
	}
	if (indices[0] != -1)
	{
		for (int i = 0; i < 4; i++)
		{
			_fallingBlock->Blocks()[i]->position = grid[_fallingBlock->Blocks()[i]->getIndexY()][indices[i]]->position;
			_fallingBlock->Blocks()[i]->setIndexX(indices[i]);
		}
	}
}

void Grid::update(float deltaTime)
{
	moveBlock();
}