#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow* window;
	int screenWidth, screenHeight;
	void init(int width, int height);
	bool isOpen();
	void processInput();
	void swapBuffers();
	void terminate();
};