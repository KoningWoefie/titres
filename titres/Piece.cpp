#include "Piece.h"

Piece::Piece(int i) 
{
	this->createPiece(i);
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

			b1->setIndices(5, 0);
			b2->setIndices(6, 0);
			b3->setIndices(5, 1);
			b4->setIndices(6, 1);

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
			for (int i = 4; i < 8; i++)
			{
				Block* b1 = new Block(0, 0);

				b1->AddSprite("assets/block.tga");

				b1->setIndices(i, 0);

				_blocks.push_back(b1);

				this->AddChild(b1);
			}
			break;
		}
		case 2:
		{
			//make L piece
			break;
		}
		case 3:
		{
			//make J piece
			break;
		}
		case 4:
		{
			//make T piece
			break;
		}
		case 5:
		{
			//make Z piece
			break;
		}
		case 6:
		{
			//make S piece
			break;
		}
	}
}
