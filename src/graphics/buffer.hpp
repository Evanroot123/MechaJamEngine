#pragma once
#include <glad/glad.h>


// for now this class will serve multiple roles: batched buffer, fixed buffer
// based on how functions are called. later can break these down into separate classes
class Buffer
{
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	void generateBatched();
	void generateFixed(unsigned int numVertices);
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void bufferData();
	void bind();

private:
	static const unsigned int vertexCapacity = 1000U;
};