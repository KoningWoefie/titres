#include <common/resourcemanager.h>
#include <common/config.h>

#include <iostream>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

ResourceManager::ResourceManager()
{
	std::cout << "Creating ResourceManager" << std::endl;
}

ResourceManager::~ResourceManager()
{
	std::cout << "Destroying ResourceManager" << std::endl;
}

Sprite* ResourceManager::GetTexture(const std::string& fileName, bool spriteSheet, float uvH, float uvW)
{
	if (_textures[fileName] != nullptr)
	{
		return _textures[fileName];
	}
	if (spriteSheet)
	{
		Sprite* ss = new Sprite(fileName, uvH, uvW);
		ss->loadTGA(fileName);
		_textures[fileName] = ss;
		return ss;
	}
	Sprite* s = new Sprite(fileName);
	s->loadTGA(fileName);
	_textures[fileName] = s;
	return s;
}