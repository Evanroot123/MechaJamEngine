#pragma once

#include <map>
#include <string>
#include "texture.hpp"

class ResourceManager
{
public:
	ResourceManager() = delete;
	static void loadTexture(const char* file, bool alpha, std::string name);
	static std::map<std::string, Texture> textures;
};