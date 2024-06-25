#include "resourcemanager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture> ResourceManager::textures;

void ResourceManager::loadTexture(const char* file, bool alpha, std::string name)
{
	Texture texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &width, &height, &channels, 0);
	texture.generate(width, height, data);
	stbi_image_free(data);

	textures[name] = texture;
}
