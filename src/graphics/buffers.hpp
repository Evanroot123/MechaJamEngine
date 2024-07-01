#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm.hpp>

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

	void generate();
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void bufferData();
	void bind();

private:
	static const unsigned int vertexCapacity = 1000U;
};

class InstancedQuadBuffer
{
public:
	unsigned int vao;
	unsigned int vertexVbo;
	unsigned int instanceVbo;
	int vertexCount = 0;

	void generate(float* vertices, int numVertices);
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void pushVertex(glm::mat4& transform);
	void flush();
	void bind();

private:
	int vertexCapacity = 1000;
	glm::mat4 vertexData[1000];
};