#pragma once
#include <vector>
#include "shader.hpp"
#include "gameobject.hpp"

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
	void draw(std::vector<GameObject>& objects);

private:
	std::vector<Shader> shaders;
};