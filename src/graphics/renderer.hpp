#pragma once
#include <vector>
#include "shader.hpp"
#include "buffers.hpp"
#include "gameobject.hpp"
#include "window.hpp"

enum ShaderPrograms
{
	TEXT,
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
	void drawBatched(std::vector<GameObject>& objects);
	void drawSprite(GameObject& object);

private:
	std::vector<Shader> shaders;
	FixedQuadBuffer spriteBuffer;
	InstancedQuadBuffer instanceBuffer;
	Window* window;
};