#pragma once
#include <vector>
#include "shader.hpp"
#include "buffers.hpp"
#include "gameobject.hpp"
#include "window.hpp"
#include "text.hpp"
#include "vertices.h"
#include "grid.hpp"

enum ShaderPrograms
{
	SINGLE_TEXT,
	INSTANCE_TEXT,
	SINGLE_SPRITE,
	INSTANCE_SPRITE,
	SQUARE_GRID,
};

class Renderer
{
public:
	glm::vec2 cameraPosition;

	void getGPUInfo();
	void enableDebugContext();
	void init(Window* window);
	void clear();
	void startFrame(Camera& camera);
	void endFrame();
	void drawBatched(const std::vector<GameObject>& objects);
	void drawSprite(const GameObject& object);
	void drawText(const Character& character, glm::vec2 position);
	void drawText(std::string text, Text& textObject, glm::vec2 pos, float scale, glm::vec3 color);
	void testDrawText(Texture& batchedTexture, glm::vec2 size, glm::vec2 position);
	void drawGrid(const Grid& grid, glm::vec2 gridPosition);

private:
	std::vector<Shader> shaders;
	FixedQuadBuffer spriteBuffer;
	FixedQuadBuffer textBuffer;
	InstancedQuadBuffer<glm::mat4> instanceBuffer;
	InstancedQuadBuffer<Vertex1> textInstanceBuffer;
	InstancedQuadBuffer<glm::vec2> gridInstanceBuffer;
	Window* window;
};