#pragma once
#include <vector>
#include "shader.hpp"

enum ShaderPrograms
{
	TEXT,
	BASIC_SPRITE
};

class Renderer
{
public:
	void getGPUInfo();
	void enableDebugContext();
	void init();
	void clear();
	void draw();

private:
	std::vector<Shader> shaders;
};