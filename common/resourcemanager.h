#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <common/sprite.h>
#include <GL/glew.h>

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	Sprite* GetTexture(const std::string& fileName);

private:
	std::map<std::string, Sprite*> _textures;
};

#endif // !RESOURCEMANAGER_H
