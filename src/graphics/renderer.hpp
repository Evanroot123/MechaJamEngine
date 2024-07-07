#pragma once
#include <vector>
#include "shader.hpp"
#include "buffers.hpp"
#include "gameobject.hpp"
#include "window.hpp"
#include "text.hpp"

enum ShaderPrograms
{
	SINGLE_TEXT,
	SINGLE_SPRITE,
	INSTANCE_SPRITE,
};

class Renderer
{
public:
	glm::vec2 cameraPosition;

	void getGPUInfo();
	void enableDebugContext();
	void init(Window* window);
	void clear();
	void startFrame();
	void endFrame();
	void drawBatched(const std::vector<GameObject>& objects);
	void drawSprite(const GameObject& object);
	void drawText(const Character& character, glm::vec2 position);
	void drawText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);

private:
	std::vector<Shader> shaders;
	FixedQuadBuffer spriteBuffer;
	InstancedQuadBuffer instanceBuffer;
	Window* window;
};