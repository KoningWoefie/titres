#include <common/resourcemanager.h>
#include <common/config.h>

#include <iostream>

ResourceManager::ResourceManager()
{
	std::cout << "Creating ResourceManager" << std::endl;
}

ResourceManager::~ResourceManager()
{
	std::cout << "Destroying ResourceManager" << std::endl;
}

Sprite* ResourceManager::GetTexture(const std::string& fileName)
{
	if (_textures[fileName] != NULL)
	{
		return _textures[fileName];
	}
	Sprite* s = new Sprite(fileName);
	s->loadTGA(fileName);
	_textures[fileName] = s;
	return s;
}