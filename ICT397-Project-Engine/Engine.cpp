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
		//gameScenes[currentScene].Run

		//std::vector<GameObject> objects = gameScenes[currentScene].GetGameObjects();
		//We then will pass the game objects into the window/controller so they can me manipulated if needed
		//THey will then be returned and passed into the renderer for rendering
		//They will then be renderered and returned back to the scene so the changes made to them are kept
		//This does the model-View-Controller
		window->Buffer();
	}
}