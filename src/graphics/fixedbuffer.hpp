#pragma once
#include <glad/glad.h>
#include <vector>

// for now this class will serve multiple roles: batched buffer, fixed buffer
// based on how functions are called. later can break these down into separate classes
class FixedBuffer
{
public:
	unsigned int vao;
	unsigned int vbo;

	void generate(float* data, int numVertices);
	void attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data);
	void bind();
};