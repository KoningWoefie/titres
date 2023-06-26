#include "text.h"

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Text::Text()
{
	_message = "";
}

Text::~Text()
{
	ClearMessage();
}

void Text::update(float deltaTime)
{

}

void Text::ClearMessage()
{
	//for (int i = spriteSheet.size() - 1; i >= 0; i--)
	for(int i = 0; i < this->spriteSheet.size(); i++)
	{
		delete spriteSheet[i];
		spriteSheet[i] = nullptr;
	}
	this->spriteSheet.clear();
	_message = "";
}

void Text::Message(std::string m)
{
	this->ClearMessage();
	_message = m;
	//std::cout << _message << std::endl;
	float yPos = 0.0f;
	float xPos = -32.0f;
	for (int i = 0; i < m.size(); i++)
	{
		float uvH = 1.0f / 8;
		float uvW = 1.0f / 16;
		Sprite* glyph = new Sprite("fonts/font.tga", uvH, uvW);
		glyph->SetUpSize(64, 64, glyph->getTexture());

		char c = m[i];
		if (m[i] == 10)
		{
			yPos += 64;
			xPos = -32.0f;
			this->spriteSheet.push_back(glyph);
			continue;
		}
		xPos += 32;

		glyph->spritePosition[0] += xPos;
		glyph->spritePosition[0] -= (float)((m.size() / 2) * 32);

		glyph->spritePosition[1] = yPos;

		int index = (int)c - 32;

		glyph->Index(index);

		this->spriteSheet.push_back(glyph);

		glyph = nullptr;
	}
}