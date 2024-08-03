#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"

class Window
{
public:
	GLFWwindow* window;
	int screenWidth, screenHeight;

	void init(int width, int height);
	bool isOpen();
	void processInput(Camera& camera);
	void swapBuffers();
	void terminate();
};