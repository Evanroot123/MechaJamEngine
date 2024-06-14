#pragma once
#include <glad/glad.h>

class Buffer
{
public:
	unsigned int vao;
	unsigned int vbo;

	void generate1();
	void bufferData();
	void bind();

private:
	static const unsigned int vertexCapacity = 1000U;
};