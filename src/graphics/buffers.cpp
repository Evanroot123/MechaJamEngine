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


BatchedBuffer::BatchedBuffer() :vao(0), vbo(0)
{
	vertexData = new glm::mat4[vertexCapacity];
}

BatchedBuffer::~BatchedBuffer()
{
	delete[] vertexData;
}

void BatchedBuffer::generate()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * vertexCapacity, nullptr, GL_DYNAMIC_DRAW);
	for (int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
		glVertexAttribDivisor(i, 1);
	}
}

void BatchedBuffer::attributePointer(GLuint index, GLint numComponents, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* data)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, numComponents, type, normalized, stride, data);
}

void BatchedBuffer::pushVertex(glm::mat4& transform)
{
	unsigned int vertexCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertexCount, nullptr);
}

void BatchedBuffer::flush()
{

}

void BatchedBuffer::bind()
{
	glBindVertexArray(vao);
}
