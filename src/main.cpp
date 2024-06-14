#include "renderer.hpp"
#include "window.hpp"

int main()
{
	Window window;
	window.init(800, 600);

	Renderer renderer;
	renderer.init();

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