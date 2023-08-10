#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <common/sprite.h>
#include <common/mesh.h>
#include <GL/glew.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	Sprite* GetTexture(const std::string& fileName, bool spriteSheet = false, float uvH = 1.0f, float uvW = 1.0f);

	Mesh* GetMesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot);

private:
	std::map<std::string, Sprite*> _textures;
	std::map<std::string, Mesh*> _meshes;
};

#endif // !RESOURCEMANAGER_H
