#pragma once

class GLFWwindow;

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