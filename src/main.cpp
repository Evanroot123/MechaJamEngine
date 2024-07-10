#include <iostream>

#include "renderer.hpp"
#include "window.hpp"
#include "gameobject.hpp"
#include "resourcemanager.hpp"
#include "stopwatch.hpp"
#include "text.hpp"
#include "teststrings.hpp"

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
	Window window;
	window.init(1920, 1080);
    
	Renderer renderer;
	renderer.init(&window);
	//renderer.getGPUInfo();
    
	StopWatch sw;
	ResourceManager::loadTexture("resources\\textures\\green-circle.png", true, "shiboopy");
	
	Text text{ 24 };
	//text.loadCharacters();
	text.loadBatchedCharacters();

	GameObject shiboopy;
	shiboopy.posX = 50;
	shiboopy.posY = 50;
	shiboopy.texture = &ResourceManager::textures.at("shiboopy");
	shiboopy.sizeX = shiboopy.texture->width;
	shiboopy.sizeY = shiboopy.texture->height;

	//std::vector<GameObject> objects;
	
	//for (int i = 0; i < 800; i += 1)
	//{
	//	for (int j = 0; j < 600; j += 1)
	//	{
	//		shiboopy.posX = i;
	//		shiboopy.posY = j;
	//		objects.push_back(shiboopy);
	//	}
	//}

	//std::cout << objects.size() << std::endl;
    
	while (window.isOpen())
	{
		window.processInput();
		renderer.clear();
		renderer.startFrame();

		//startFrameImGui();
		//ImGui::Begin("Hello, world!");
		//ImGui::Text("This is some useful text.");
		//ImGui::End();
		//endFrameImGui();

		//renderer.drawText(text.characters['a'], {50, 50});
		//renderer.testDrawText(text.batchedCharactersTexture, { 512, 512 }, { 400, 300 });
		


		sw.start();
		renderer.drawText(loremIpsum, text, { 0, 1032 }, 1.0f, { 0.7, 0.7, 0.7 });
		sw.stop();
		std::cout << std::fixed;
		std::cout << "elapsed microseconds: " << sw.elapsedMicroseconds() << std::endl;

		//renderer.drawText("Q", text, { 300, 400 }, 1.0f, { 0.7, 0.7, 0.7 });
		//renderer.drawText("e", text, { 300, 400 }, 1.0f, { 0.7, 0.7, 0.7 });
		//renderer.drawText("l", text, { 300, 400 }, 1.0f, { 0.7, 0.7, 0.7 });

		//renderer.drawText("S", text, { 310, 400 }, 1.0f, { 0.7, 0.7, 0.7 });

		//sw.start();
		//for (const GameObject& obj : objects)
		//{
		//	renderer.drawSprite(obj);
		//}
		//renderer.drawBatched(objects);
		//sw.stop();
		//std::cout << std::fixed;
		//std::cout << "elapsed microseconds: " << sw.elapsedMicroseconds() << std::endl;

		renderer.endFrame();
		window.swapBuffers();
	}
    
	window.terminate();
	return 0;
}