#include "Piece.h"

Piece::Piece(int i) 
{
	this->createPiece(i);
	this->rotationSortOf = 0;
	switch (i)
	{
	case 0:
	{
		//make O piece

		break;
	}
	case 1:
	{
		//make I piece
		_positions = 
		{
			{	{-2,2},{-1,1},{0,0},{1,-1}	}, //0
			{	{2,-2},{1,-1},{0,0},{-1,1}	}, //1
		};
		break;
	}
	case 2:
	{
		//make L piece
		_positions =
		{
			{	{-1,-1},{-2,0},{0,0},{1,1}	}, //0
			{	{1,-1},{0,-2},{0,0},{-1,1}	}, //1
			{	{1,1},{2,0},{0,0},{-1,-1}	}, //2
			{	{-1,1},{0,2},{0,0},{1,-1}	}, //3
		};
		break;
	}
	case 3:
	{
		//make J piece
		_positions =
		{
			{	{1,1},{0,2},{0,0},{-1,-1}	}, //0
			{	{-1,1},{-2,0},{0,0},{1,-1}	}, //1
			{	{-1,-1},{0,-2},{0,0},{1,1}	}, //2
			{	{1,-1},{2,0},{0,0},{-1,1}	}, //3
		};
		break;
	}
	case 4:
	{
		_positions =
		{
			{	{-1,-1},{-1,1},{0,0},{1,1}	}, //0
			{	{1,-1},{-1,-1},{0,0},{-1,1}	}, //1
			{	{1,1},{1,-1},{0,0},{-1,-1}	}, //2
			{	{-1,1},{1,1},{0,0},{1,-1}	}, //3
		};
		break;
	}
	case 5:
	{
		_positions =
		{
			{	{-2,0},{-1,-1},{0,0},{1,-1}	},
			{	{2,0},{1,1},{0,0},{-1,1}	},
		};
		break;
	}
	case 6:
	{
		_positions =
		{
			{	{0,-2},{-1,-1},{0,0},{-1,1}	},
			{	{0,2},{1,1},{0,0},{1,-1}	},
		};
		break;
	}
	}
}

Piece::~Piece() 
{ 
}

void Piece::update(float deltaTime)
{

}

void Piece::createPiece(int i)
{
	switch (i)
	{
		case 0:
		{
			//make O piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(4, 0);
			b2->setIndices(5, 0);
			b3->setIndices(4, 1);
			b4->setIndices(5, 1);

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);

			break;
		}
		case 1:
		{
			//make I piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			_anchorBlock = b3;

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(3, 4);
			b2->setIndices(4, 4);
			b3->setIndices(5, 4);
			b4->setIndices(6, 4);

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
		case 2:
		{
			//make L piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(4, 1);
			b2->setIndices(4, 2);
			b3->setIndices(5, 1);
			b4->setIndices(6, 1);

			_anchorBlock = b3;

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
		case 3:
		{
			//make J piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(6, 3);
			b2->setIndices(6, 4);
			b3->setIndices(5, 3);
			b4->setIndices(4, 3);

			_anchorBlock = b3;

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
		case 4:
		{
			//make T piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(4, 2);
			b2->setIndices(5, 3);
			b3->setIndices(5, 2);
			b4->setIndices(6, 2);

			_anchorBlock = b3;

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
		case 5:
		{
			//make z piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(4, 2);
			b2->setIndices(5, 2);
			b3->setIndices(5, 3);
			b4->setIndices(6, 3);

			_anchorBlock = b3;

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
		case 6:
		{
			//make S piece
			Block* b1 = new Block(0, 0);
			Block* b2 = new Block(0, 0);
			Block* b3 = new Block(0, 0);
			Block* b4 = new Block(0, 0);

			b1->AddSprite("assets/block.tga");
			b2->AddSprite("assets/block.tga");
			b3->AddSprite("assets/block.tga");
			b4->AddSprite("assets/block.tga");

			b1->setIndices(6, 0);
			b2->setIndices(5, 0);
			b3->setIndices(5, 1);
			b4->setIndices(4, 1);

			_anchorBlock = b3;

			_blocks.push_back(b1);
			_blocks.push_back(b2);
			_blocks.push_back(b3);
			_blocks.push_back(b4);

			this->AddChild(b1);
			this->AddChild(b2);
			this->AddChild(b3);
			this->AddChild(b4);
			break;
		}
	}
}

void Piece::rotatePiece()
{
	rotationSortOf++;
	for (int i = 0; i < 4; i++)
	{
		_blocks[i]->setIndicesSortOf(_positions[rotationSortOf][i][0], _positions[rotationSortOf][i][1]);
	}
	if (rotationSortOf == (_positions.size() - 1))
	{
		rotationSortOf = -1;
	}
}
