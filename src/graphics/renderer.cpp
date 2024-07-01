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
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &textureUnits);
	std::cout << "max vertex uniform components: " << textureUnits << std::endl;
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

void Renderer::init(Window* window)
{
	enableDebugContext();

	cameraPosition.x = 0;
	cameraPosition.y = 0;
	this->window = window;

	// the order of this is hardcoded to the ShaderPrograms enum
	Shader shader;
	shader.compile(vertexShaderGlyph, fragmentShaderGlyph);
	shaders.push_back(shader);
	shader.compile(singleSpriteVertex, singleSpriteFragment);
	shaders.push_back(shader);
	shader.compile(instancedSpriteVertex, instancedSpriteFragment);
	shaders.push_back(shader);

	float vertices[] = {
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f
	};

	spriteBuffer.generate(vertices, sizeof(vertices) / sizeof(vertices[0]));
	spriteBuffer.attributePointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	instanceBuffer.generate(vertices, sizeof(vertices) / sizeof(vertices[0]));
}

void Renderer::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::startFrame()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaders[SINGLE_SPRITE].use();
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(cameraPosition.x, cameraPosition.y, 0));
	shaders[SINGLE_SPRITE].setMatrix4("view", view, false);
	glm::mat4 projection = glm::ortho(0.0f, (float)window->screenWidth, 0.0f, (float)window->screenHeight, -1.0f, 1.0f);
	shaders[SINGLE_SPRITE].setMatrix4("projection", projection, false);

	shaders[INSTANCE_SPRITE].use();
	shaders[INSTANCE_SPRITE].setMatrix4("view", view, false);
	shaders[INSTANCE_SPRITE].setMatrix4("projection", projection, false);
}

void Renderer::endFrame()
{

}

void Renderer::drawBatched(std::vector<GameObject>& objects)
{
	if (objects.size() <= 0)
		return;

	shaders[INSTANCE_SPRITE].use();
	glActiveTexture(GL_TEXTURE0);
	objects[0].texture->bind();
	shaders[INSTANCE_SPRITE].setInteger("image", 0);
	instanceBuffer.bind();

	for (const GameObject& object : objects)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(object.posX, object.posY, 0));
		model = glm::scale(model, glm::vec3(object.sizeX, object.sizeY, 1));
		instanceBuffer.pushVertex(model);
	}

	instanceBuffer.flush();
}

void Renderer::drawSprite(GameObject& object)
{
	shaders[SINGLE_SPRITE].use();
	glActiveTexture(GL_TEXTURE0);
	object.texture->bind();
	shaders[SINGLE_SPRITE].setInteger("image", 0);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(object.posX, object.posY, 0));
	model = glm::scale(model, glm::vec3(object.sizeX, object.sizeY, 1));
	shaders[SINGLE_SPRITE].setMatrix4("model", model, false);
	spriteBuffer.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
