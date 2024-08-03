#include "window.hpp"
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static bool scrolled = false;
static double scroll = 0.0f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrolled = true;
	scroll = yoffset;
}

void Window::init(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// set sticky keys
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	
	screenWidth = width;
	screenHeight = height;

	// Initialize ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430"); // Replace #version 130 with your OpenGL version

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

void Window::processInput(Camera& camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	static double cursorX, cursorY;
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		double currentX, currentY;
		glfwGetCursorPos(window, &currentX, &currentY);
		camera.pan(currentX - cursorX, currentY - cursorY);
		cursorX = currentX;
		cursorY = currentY;
	}
	else
	{
		glfwGetCursorPos(window, &cursorX, &cursorY);
	}

	if (scrolled)
	{
		camera.zoom(scroll);
		scrolled = false;
	}
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::terminate()
{
	glfwTerminate();
}

