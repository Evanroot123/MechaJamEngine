#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm.hpp>
#include <iostream>

class FixedQuadBuffer
{
public:
	unsigned int vao;
	unsigned int vbo;

	void generate(float* data, int numVertices);
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void bind();
};

class BatchedBuffer
{
public:
	unsigned int vao;
	unsigned int vbo;
	int vertexCount = 0;

	BatchedBuffer();
	~BatchedBuffer();
	void generate();
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void pushVertex(glm::mat4& transform);
	void flush();
	void bind();

private:
	int vertexCapacity = 10000;
	glm::mat4* vertexData;
};

template<typename T>
class InstancedQuadBuffer
{
public:
	unsigned int vao = 0;
	unsigned int vertexVbo = 0;
	unsigned int instanceVbo = 0;
	int vertexCount = 0;

private:
	int vertexCapacity = 10000;
	T* vertexData;

public:
	InstancedQuadBuffer()
	{
		vertexData = new T[vertexCapacity];
	}

	~InstancedQuadBuffer()
	{
		delete[] vertexData;
	}

	void generate(float* vertices, int numVertices)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vertexVbo);
		glGenBuffers(1, &instanceVbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertexCapacity, nullptr, GL_DYNAMIC_DRAW);
	}

	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
		glVertexAttribDivisor(index, 1);
	}

	void attributePointerMat4(GLuint index, int offset)
	{
		for (int i = 0; i < 4; i++)
		{
			glEnableVertexAttribArray(index + i);
			glVertexAttribPointer(index + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i + offset));
			glVertexAttribDivisor(index + i, 1);
		}
	}

	void pushVertex(T& vertex)
	{
		if (vertexCount >= vertexCapacity)
			flush();

		vertexData[vertexCount++] = vertex;
	}

	void flush()
	{
		if (vertexCount <= 0)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(T) * vertexCount, vertexData);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, vertexCount);
		vertexCount = 0;
	}

	void bind()
	{
		glBindVertexArray(vao);
	}
};