#pragma once
#include <vector>
#include "shader.hpp"
#include "fixedbuffer.hpp"
#include "gameobject.hpp"
#include "window.hpp"

enum ShaderPrograms
{
	TEXT,
	SINGLE_SPRITE,
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
	void draw(std::vector<GameObject>& objects);
	void drawSprite(GameObject& object);

private:
	std::vector<Shader> shaders;
	FixedBuffer spriteBuffer;
	Window* window;
};