#include <iostream>
#include <cstdlib>
#include <ctime>

#include "renderer.hpp"
#include "window.hpp"
#include "gameobject.hpp"
#include "resourcemanager.hpp"
#include "stopwatch.hpp"
#include "text.hpp"
#include "teststrings.hpp"
#include "datainitialization.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void startFrameImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void endFrameImGui() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
	srand(time(NULL));

	Window window;
	window.init(1920, 1080);
    
	Renderer renderer;
	renderer.init(&window);

	Camera camera;
    
	StopWatch sw;
	ResourceManager::loadTexture("resources\\textures\\green-circle.png", true, "shiboopy");
	ResourceManager::loadTexture("resources\\textures\\Sprite-0001.png", true, "sample_tile");
	
	Text text{ 24 };
	text.loadBatchedCharacters();

	GameObject shiboopy{ 50, 50, &ResourceManager::textures.at("sample_tile") };
	Grid testGrid{ 20, 20, 64, 64, &ResourceManager::textures.at("sample_tile") };
	initializeTileMapTexturePos(testGrid);
    
	while (window.isOpen())
	{
		window.processInput(camera);
		renderer.clear();
		renderer.startFrame(camera);

		renderer.drawGrid(testGrid, { 0, 0 });
		//renderer.drawSprite(shiboopy);

		//startFrameImGui();
		//ImGui::Begin("Hello, world!");
		//ImGui::Text("This is some useful text.");
		//ImGui::End();
		//endFrameImGui();

		renderer.endFrame();
		window.swapBuffers();
	}
    
	window.terminate();
	return 0;
}