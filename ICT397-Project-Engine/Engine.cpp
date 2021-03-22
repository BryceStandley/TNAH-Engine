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
	}
	else
	{
		render = new GladRenderer();
		render->DepthTest();
	}

	currentScene = 0;

	Scene one("Game", "cfshader.glsl", "cvshader.glsl", "grass.jpg");
	gameScenes.push_back(one);
}

Engine::~Engine()
{
	if (window != NULL)
		delete[] window;
}

void Engine::Run()
{
	while (running)
	{
		window->Clear();

		Terrain *t = gameScenes[currentScene].GetTerrain();

		//Scene projection
		window->Projection();
		window->Restart();

		if (gameScenes[currentScene].GetSceneName() == "menu")
		{
			std::cout << "This is menu" << std::endl;
		}
		else
		{
			//Terrain
			window->SetShader(t->shader);
			render->BindTexture(t->terrainTextureID);
			render->RenderTerrain(t->GetVao(), t->GetSize());

			//for (int i = 0; i < gameScenes[currentScene].gameObjects.size(); i++)
			//{
				//maniplute game object
				//set shader
				//bind texture
				//render game object
				//send manipulations back
			//}
		}

		window->Buffer();
	}
}