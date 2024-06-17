#include "renderer.hpp"
#include <iostream>
#include <glad/glad.h>
#include "debugging.hpp"
#include "shaderstrings.hpp"

void Renderer::getGPUInfo()
{
	int textureUnits = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	std::cout << "texture units: " << textureUnits << std::endl;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureUnits);
	std::cout << "max combined texture units: " << textureUnits << std::endl;
}

void Renderer::enableDebugContext()
{
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
	}
}

void Renderer::init()
{
	// the order of this is hardcoded to the ShaderPrograms enum
	Shader shader;
	shader.compile(vertexShaderGlyph, fragmentShaderGlyph);
	shaders.push_back(shader);
	shader.compile(vertexShaderBasic, fragmentShaderBasic);
	shader.setVector4f("uColor", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shaders.push_back(shader);
}

void Renderer::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(std::vector<GameObject>& objects)
{
	// 

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
