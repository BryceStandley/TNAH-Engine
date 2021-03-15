#include "Engine.h"

Engine::Engine()
{
	//Checks if glfw/glew is a thing
	window = new GlewWindow();
	bool check = window->Init("Engine", 1280, 720);
	if (!check)
	{
		running = true;
	}
	else
	{
		running = false;
	}
		
	this->currentScene = 0;
}

Engine::~Engine()
{
	if (window != NULL)
		delete[] window;
}

void Engine::Run()
{
	while (!running)
	{
		window->Clear();
		running = window->GameInput();
		//gameScenes[currentScene].Run();
		//In the loop we get the model information from the scene manager
		//We also get the input information
		//Using these we edit the model information based of the input information we get
		//And pass the model information into the view information(renderer) and render the scene
		//This does the model-View-Controller
		window->Buffer();
	}
}