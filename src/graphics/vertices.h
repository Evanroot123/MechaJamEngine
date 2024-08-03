#pragma once
#include <glm.hpp>

struct Vertex1
{
	glm::vec4 texInfo;
	glm::mat4 transform;
};

struct Vertex2
{
	glm::vec2 texPos; // only need texPos because grid textures are all the same size
};