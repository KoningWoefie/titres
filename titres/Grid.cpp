#include "Grid.h" 
Grid::Grid(int gridSizeX, int gridSizeY) 
{
	for (int y = 0; y < gridSizeY; y++)
	{
		std::vector<Block*> row;
		for (int x = 0; x < gridSizeX; x++)
		{
			Block* b = new Block(x * 16 + 8, y * 16 + 8);
			row.push_back(b);
			this->AddChild(b);
		}
		grid.push_back(row);
	}
} 
Grid::~Grid() 
{
}

void Grid::update(float deltaTime)
{

}
