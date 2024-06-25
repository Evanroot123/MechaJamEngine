#include "batchedbuffer.hpp"

void BatchedBuffer::generateBatched()
{
	unsigned int vertexSize = 4;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCapacity, nullptr, GL_DYNAMIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

void BatchedBuffer::generateFixed(unsigned int numVertices)
{

}

void BatchedBuffer::attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchedBuffer::attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
}

void BatchedBuffer::bufferData()
{
	unsigned int vertexCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertexCount, nullptr);
}

void BatchedBuffer::bind()
{
	glBindVertexArray(vao);
}
