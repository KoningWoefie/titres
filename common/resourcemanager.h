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

	Sprite* GetTexture(const std::string& fileName, bool spriteSheet = false, float uvH = 1.0f, float uvW = 1.0f);

private:
	std::map<std::string, Sprite*> _textures;
};

#endif // !RESOURCEMANAGER_H
