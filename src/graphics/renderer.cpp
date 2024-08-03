#include "renderer.hpp"
#include <iostream>
#include <glad/glad.h>
#include "debugging.hpp"
#include "shaderstrings.hpp"
#include "camera.hpp"

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
	shader.compile(instanceGlyphVertexShader, instanceGlyphFragmentShader);
	shaders.push_back(shader);
	shader.compile(singleSpriteVertex, singleSpriteFragment);
	shaders.push_back(shader);
	shader.compile(instancedSpriteVertex, instancedSpriteFragment);
	shaders.push_back(shader);
	shader.compile(tileMapVertex, tileMapFragment);
	shaders.push_back(shader);

	float vertices[] = {
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f
	};

	float textVertices[] = {
		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f
	};

	spriteBuffer.generate(vertices, sizeof(vertices) / sizeof(vertices[0]));
	spriteBuffer.attributePointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	textBuffer.generate(textVertices, sizeof(textVertices) / sizeof(textVertices[0]));
	textBuffer.attributePointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	instanceBuffer.generate(vertices, sizeof(vertices) / sizeof(vertices[0]));
	instanceBuffer.attributePointerMat4(1, 0);
	textInstanceBuffer.generate(textVertices, sizeof(textVertices) / sizeof(textVertices[0]));
	textInstanceBuffer.attributePointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (void*)0);
	textInstanceBuffer.attributePointerMat4(2, sizeof(float) * 4);
	gridInstanceBuffer.generate(vertices, sizeof(vertices) / sizeof(vertices[0]));
	gridInstanceBuffer.attributePointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2), (void*)0);
}

void Renderer::clear()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::startFrame(Camera& camera)
{
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaders[SINGLE_SPRITE].use();
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(camera.pos.x + ((float)window->screenWidth * 0.5 * camera.zoomLevel), camera.pos.y + ((float)window->screenHeight * 0.5 * camera.zoomLevel), 0));
	shaders[SINGLE_SPRITE].setMatrix4("view", view, false);
	glm::mat4 projection = glm::ortho(0.0f, (float)window->screenWidth * camera.zoomLevel, 0.0f, (float)window->screenHeight * camera.zoomLevel, -1.0f, 1.0f);
	shaders[SINGLE_SPRITE].setMatrix4("projection", projection, false);

	shaders[INSTANCE_SPRITE].use();
	shaders[INSTANCE_SPRITE].setMatrix4("view", view, false);
	shaders[INSTANCE_SPRITE].setMatrix4("projection", projection, false);

	shaders[SINGLE_TEXT].use();
	shaders[SINGLE_TEXT].setMatrix4("view", view, false);
	shaders[SINGLE_TEXT].setMatrix4("projection", projection, false);

	shaders[INSTANCE_TEXT].use();
	shaders[INSTANCE_TEXT].setMatrix4("view", view, false);
	shaders[INSTANCE_TEXT].setMatrix4("projection", projection, false);

	shaders[SQUARE_GRID].use();
	shaders[SQUARE_GRID].setMatrix4("view", view, false);
	shaders[SQUARE_GRID].setMatrix4("projection", projection, false);
}

void Renderer::endFrame()
{

}

void Renderer::drawBatched(const std::vector<GameObject>& objects)
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

void Renderer::drawSprite(const GameObject& object)
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

void Renderer::drawText(const Character& character, glm::vec2 position)
{
	shaders[SINGLE_TEXT].use();
	glActiveTexture(GL_TEXTURE0);
	character.texture.bind();
	shaders[SINGLE_TEXT].setInteger("text", 0);
	shaders[SINGLE_TEXT].setVector3f("textColor", 1.0f, 1.0f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0));
	model = glm::scale(model, glm::vec3(character.size.x, character.size.y, 1));
	shaders[SINGLE_TEXT].setMatrix4("model", model, false);
	spriteBuffer.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawText(std::string text, Text& textObject, glm::vec2 pos, float scale, glm::vec3 color)
{
	shaders[INSTANCE_TEXT].use();
	glActiveTexture(GL_TEXTURE0);
	textObject.batchedCharactersTexture.bind();
	shaders[INSTANCE_TEXT].setInteger("text", 0);
	shaders[INSTANCE_TEXT].setVector3f("textColor", color);
	shaders[INSTANCE_TEXT].setVector2f("texSize", textObject.batchedCharactersTexture.width, textObject.batchedCharactersTexture.height);
	textInstanceBuffer.bind();

	Vertex1 instanceData;
	//instanceData.texInfo.z = textObject.batchedCharactersTexture.width;
	//instanceData.texInfo.w = textObject.batchedCharactersTexture.height;
	std::string::const_iterator c;

	int lineWidth = pos.x;
	int lineHeight = pos.y;
	for (c = text.begin(); c != text.end(); c++)
	{
		CharacterBatched bc = textObject.batchedCharacters[*c];

		if (*c == ' ')
		{
			lineWidth += (bc.advance >> 6);
			continue;
		}
		if (*c == '\n')
		{
			lineWidth = pos.x;
			lineHeight -= textObject.pixelHeight;
			continue;
		}

		int xpos = lineWidth + bc.bearing.x;
		int ypos = lineHeight - (bc.size.y - bc.bearing.y);
		// adjust for center
		xpos += bc.size.x / 2;
		ypos += bc.size.y / 2;
		instanceData.transform = glm::mat4(1.0f);
		instanceData.transform = glm::translate(instanceData.transform, glm::vec3(xpos, ypos, 0));
		instanceData.transform = glm::scale(instanceData.transform, glm::vec3(bc.size.x, bc.size.y, 0));
		instanceData.texInfo.x = bc.pos.x;
		instanceData.texInfo.y = bc.pos.y;
		instanceData.texInfo.z = bc.size.x;
		instanceData.texInfo.w = bc.size.y;
		textInstanceBuffer.pushVertex(instanceData);
		lineWidth += (bc.advance >> 6);
	}

	textInstanceBuffer.flush();
}

void Renderer::testDrawText(Texture& batchedTexture, glm::vec2 size, glm::vec2 position)
{
	shaders[SINGLE_TEXT].use();
	glActiveTexture(GL_TEXTURE0);
	batchedTexture.bind();
	shaders[SINGLE_TEXT].setInteger("text", 0);
	shaders[SINGLE_TEXT].setVector3f("textColor", 1.0f, 1.0f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1));
	shaders[SINGLE_TEXT].setMatrix4("model", model, false);
	textBuffer.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawGrid(const Grid& grid, glm::vec2 gridPosition)
{
	shaders[SQUARE_GRID].use();
	glActiveTexture(GL_TEXTURE0);
	grid.texture->bind();
	shaders[SQUARE_GRID].setInteger("tileset", 0);
	shaders[SQUARE_GRID].setVector2f("gridPos", glm::vec2{ gridPosition.x, gridPosition.y });
	shaders[SQUARE_GRID].setVector2f("texSize", glm::vec2{ grid.texture->width, grid.texture->height});
	shaders[SQUARE_GRID].setVector2i("gridSize", glm::ivec2{grid.width, grid.height});
	shaders[SQUARE_GRID].setInteger("gridWidthPixels", grid.tileWidth);
	shaders[SQUARE_GRID].setInteger("gridHeightPixels", grid.tileHeight);
	gridInstanceBuffer.bind();

	// loop thru tiles in grid
	for (int i = 0; i < grid.width; i++)
	{
		for (int j = 0; j < grid.height; j++)
		{
			// the instance data is the uv positions for each tile in the tilemap atlas
			// there might be a better and simpler way to do this
			gridInstanceBuffer.pushVertex(grid.tileTypeToTexPos.at(grid.at(i, j)->type));
		}
	}

	gridInstanceBuffer.flush();
}