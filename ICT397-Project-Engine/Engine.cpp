#include "Engine.h"

Engine::Engine()
{
	//Checks if glfw/glew is a thing
	window = new GlewWindow();
	window->FrameBuffer();
	bool check = window->Init("Engine", 600, 800);
	if (!check)
	{
		running = true;
	}
	else
	{
		running = false;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
	currentScene = 0;

	Scene one("First Test", "cfshader.glsl", "cvshader.glsl", "grass.jpg");
	gameScenes.push_back(one);
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
		//running = window->GameInput();
		Terrain *t = gameScenes[0].GetTerrain();
		window->Projection(t);
		//In the loop we get the model information from the scene manager
		//We also get the input information
		//Using these we edit the model information based of the input information we get
		//And pass the model information into the view information(renderer) and render the scene
		//This does the model-View-Controller
		window->Buffer();
	}
}