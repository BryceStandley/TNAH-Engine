#include "Engine.h"

Engine::Engine()
{
	if (glfwInit())
	{
		window = new GlfwWindow();
		window->Init("Engine", 600, 800);
		window->FrameBuffer();
		running = true;
	}
	else
	{
		running = false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		running = false;
	}
	else
	{
		render = new GladRenderer();
		render->DepthTest();
	}

	currentScene = 0;

	Scene one("Game", "fragment.glsl", "vertex.glsl", "grass.jpg");
	one.gameRenderer = render;
	gameScenes.push_back(one);
}

Engine::~Engine()
{
	if (window != NULL)
		delete[] window;
}

void Engine::Run()
{
	float deltaTime;
	while (running)
	{
		deltaTime = window->GetTime();

		window->Update();
		gameScenes[currentScene].Run(window->GetLens());
		window->UpdateCamera(gameScenes[currentScene].player.GetPos());
		//gameScenes[currentScene].player.Info();
		running = window->GameInput(deltaTime);
		window->MouseMove();

		window->Buffer();
	}
}

void Engine::InitiliseScene()
{
	for (int i = 0; i < totalScenes; i++)
	{
		//Initialise scene, getting file names, ect
		Scene temp("sceneName");
		gameScenes.push_back(temp);
	}
}