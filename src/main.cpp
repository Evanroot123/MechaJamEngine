#include <iostream>

#include "renderer.hpp"
#include "window.hpp"
#include "gameobject.hpp"
#include "resourcemanager.hpp"

int main()
{
	Window window;
	window.init(800, 600);
    
	Renderer renderer;
	renderer.init(&window);
	//renderer.getGPUInfo();
    
	ResourceManager::loadTexture("resources\\textures\\green-circle.png", true, "shiboopy");
    
	GameObject shiboopy;
	shiboopy.posX = 50;
	shiboopy.posY = 50;
	shiboopy.texture = &ResourceManager::textures["shiboopy"];
	shiboopy.sizeX = shiboopy.texture->width;
	shiboopy.sizeY = shiboopy.texture->height;
    
	while (window.isOpen())
	{
		window.processInput();
		renderer.clear();
		renderer.startFrame();
		renderer.drawSprite(shiboopy);
		renderer.endFrame();
		window.swapBuffers();
	}
    
	window.terminate();
	return 0;
}