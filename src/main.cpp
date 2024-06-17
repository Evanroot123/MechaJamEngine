#include "renderer.hpp"
#include "window.hpp"
#include "gameobject.hpp"

int main()
{
	Window window;
	window.init(800, 600);

	Renderer renderer;
	renderer.init();

	GameObject shiboopy;
	shiboopy.posX = 50;
	shiboopy.posY = 50;

	std::vector<GameObject> gameObjects;
	gameObjects.push_back(shiboopy);

	while (window.isOpen())
	{
		window.processInput();
		renderer.clear();
		renderer.draw();
		window.swapBuffers();
	}

	window.terminate();
	return 0;
}