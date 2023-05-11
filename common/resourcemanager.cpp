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

GLuint ResourceManager::GetTexture(const std::string& fileName, Sprite* s)
{
	if (_textures[fileName] != nullptr)
	{
		return _textures[fileName]->getTexture();
	}
	else
	{
		s->setTexture(s->loadTGA());
		_textures[fileName] = s;
		return s->getTexture();
	}
}