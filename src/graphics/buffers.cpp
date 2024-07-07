#include "buffers.hpp"


void FixedQuadBuffer::generate(float* vertices, int numVertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);
}

void FixedQuadBuffer::attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FixedQuadBuffer::attributePointerNoBind(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
}

void FixedQuadBuffer::bind()
{
	glBindVertexArray(vao);
}


void BatchedBuffer::generate()
{
	unsigned int vertexSize = 4;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexCapacity, nullptr, GL_DYNAMIC_DRAW);
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


void InstancedQuadBuffer::generate(float* vertices, int numVertices)
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * vertexCapacity, nullptr, GL_DYNAMIC_DRAW);
	for (int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(1 + i);
		glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
		glVertexAttribDivisor(1 + i, 1);
	}
}

void InstancedQuadBuffer::attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
}

void InstancedQuadBuffer::pushVertex(glm::mat4& transform)
{
	if (vertexCount >= vertexCapacity)
		flush();

	vertexData[vertexCount++] = transform;
}

void InstancedQuadBuffer::flush()
{
	if (vertexCount <= 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, instanceVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4) * vertexCount, vertexData);
	//glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, vertexCount);
	vertexCount = 0;
}

void InstancedQuadBuffer::bind()
{
	glBindVertexArray(vao);
}

InstancedQuadBuffer::InstancedQuadBuffer()
{
	vertexData = new glm::mat4[vertexCapacity];
}

InstancedQuadBuffer::~InstancedQuadBuffer()
{
	delete[] vertexData;
}
