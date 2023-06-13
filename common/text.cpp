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

void Text::Message(std::string m)
{
	_message = m;
	for (int i = 0; i < m.size(); i++)
	{
		float uvH = 1.0f / 8;
		float uvW = 1.0f / 16;
		Sprite* glyph = new Sprite("fonts/font.tga", uvH, uvW);

		char c = m[i];
		glyph->spritePosition[0] -= (float)((m.size()/2)*32);
		glyph->spritePosition[0] += i * 32;

		int index = (int)c - 32;

		glyph->Index(index);

		spriteSheet.push_back(glyph);
	}
}