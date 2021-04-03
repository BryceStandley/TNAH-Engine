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
	float lastFrame = 0;
	while (running)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		window->Clear();

		//Scene projection
		window->Projection();
		window->Restart();
		if (gameScenes[currentScene].GetSceneName() == "menu")
		{
			std::cout << "This is a menu" << std::endl;
		}
		else
		{
			RunTerrain();
			RunSkybox();
			RunModels();

			//gameScenes[currentScene].player.Info();
			running = window->GameInput(deltaTime);
			window->MouseMove();
		}

		window->Buffer();
	}
}

void Engine::RunTerrain()
{
	Terrain* t = gameScenes[currentScene].GetTerrain();
	window->SetShader(t->GetShader());
	render->BindTexture(t->GetTextIds());
	render->RenderTerrain(t->GetVAO(), t->GetIndicesSize());
}

void Engine::RunModels()
{
	//For each game object
	GameObject testObject = gameScenes[currentScene].GetGameObject();
	window->SetShader(testObject.shader);
	for (int i = 0; i < testObject.model.meshes.size(); i++)
	{
		render->RenderModel(testObject.shader, testObject.GenerateMatFourForMesh(i), testObject.model.meshes[i]);
	}

	//If game object is of type player
	gameScenes[currentScene].UpdatePlayer(window->GetCamera());
	window->UpdateCamera(gameScenes[currentScene].player.GetPos());
}

void Engine::RunSkybox()
{
	Skybox* s = gameScenes[currentScene].GetSkybox();
	window->SetShaderSkybox(s->GetShader());
	render->RenderSkybox(s->GetVAO(), s->GetTexture());
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