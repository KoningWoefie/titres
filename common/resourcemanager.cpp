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

Mesh* ResourceManager::GetMesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot, glm::vec2 uvOffset, int type, bool corner)
{
	if(type != -1)
	{
		char temp[128];
		sprintf(temp, "%dw_%dh_%.5fuvW_%.5fuvH_%.5fpx_%.5fpy_%.5fuvOx_%.5fuvOy_%dc_%dt", width, height, uvWidth, uvHeight, pivot.x, pivot.y, uvOffset.x, uvOffset.y, corner, type);

		std::string meshName(temp);

		if(_meshes[meshName] != nullptr)
		{
			return _meshes[meshName];
		}
		_meshes[meshName] = new Mesh(width, height, uvWidth, uvHeight, pivot, uvOffset, corner, type);
		_meshes[meshName]->generateMesh(width, height, uvWidth, uvHeight, pivot);
		std::cout << meshName << std::endl;
		return _meshes[meshName];
	}
	char temp[64];
	sprintf(temp, "%dw_%dh_%.5fuvW_%.5fuvH_%.5fpx_%.5fpy", width, height, uvWidth, uvHeight, pivot.x, pivot.y);

	std::string meshName(temp);

	if(_meshes[meshName] != nullptr)
	{
		return _meshes[meshName];
	}
	_meshes[meshName] = new Mesh(width, height, uvWidth, uvHeight, pivot);
	std::cout << uvWidth << ", " << uvHeight << std::endl;
	return _meshes[meshName];
}