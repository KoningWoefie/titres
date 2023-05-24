#include "Grid.h" 

Grid::Grid(int gridSizeX, int gridSizeY) 
{
	_gridSizeX = gridSizeX;
	_gridSizeY = gridSizeY;

	_fallingBlock = new Block(5*32+16, 16);
	_fallingBlock->setIndices(5, 0);
	_fallingBlock->AddSprite("assets/block.tga");

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
	int indexX = _fallingBlock->getIndexX();
	int indexY = _fallingBlock->getIndexY();
	if (input()->getKeyDown(Left))
	{
		if (indexX == 0)
		{
			return;
		}
		indexX -= 1;
	}
	if (input()->getKeyDown(Right))
	{
		if (indexX == _gridSizeX - 1)
		{
			return;
		}
		indexX += 1;
	}

	_fallingBlock->position = grid[indexY][indexX]->position;
	_fallingBlock->setIndexX(indexX);
}

void Grid::update(float deltaTime)
{
	moveBlock();
}
