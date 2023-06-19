#include "text.h"

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Text::Text()
{
	_message = "";
}

Text::~Text()
{

}

void Text::update(float deltaTime)
{

}

void Text::ClearMessage()
{
	for(int i = spriteSheet.size() - 1; i >= 0; i--)
	{
		delete spriteSheet[i];
		spriteSheet[i] = nullptr;
	}
	spriteSheet.clear();
	_message = "";
}

void Text::Message(std::string m)
{
	ClearMessage();
	_message = m;
	float yPos = 0.0f;
	float xPos = 0.0f;
	for (int i = 0; i < m.size(); i++)
	{
		float uvH = 1.0f / 8;
		float uvW = 1.0f / 16;
		Sprite* glyph = new Sprite("fonts/font.tga", uvH, uvW);

		char c = m[i];
		if (m[i] == 124)
		{
			yPos += 64;
			xPos = 0;
			continue;
		}
		glyph->spritePosition[0] -= (float)((m.size()/2)*32);
		xPos += 32;

		glyph->spritePosition[0] += xPos;

		glyph->spritePosition[1] = yPos;

		int index = (int)c - 32;

		glyph->Index(index);

		spriteSheet.push_back(glyph);
	}
}