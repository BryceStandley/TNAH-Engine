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
	while (running)
	{
		window->Clear();

		//Scene projection
		window->Projection();
		window->Restart();

		if (gameScenes[currentScene].GetSceneName() == "menu")
		{
			std::cout << "This is menu" << std::endl;
		}
		else
		{
			Terrain* t = gameScenes[currentScene].GetTerrain();
			Skybox* s = gameScenes[currentScene].GetSkybox();

			GameObject testObject = gameScenes[currentScene].GetGameObject(0);

			//Terrain
			//window->SetShader(t->GetShader());
			//render->BindTexture(t->GetTextIds());
			//render->RenderTerrain(t->GetVAO(), t->GetIndicesSize());
			
			//window->SetShaderSkybox(s->GetShader());
			//render->RenderSkybox(s->GetVAO(), s->GetTexture());

			for (int i = 0; i < testObject.model.meshes.size(); i++)
			{
				testObject.model.Draw(testObject.shader, testObject.GenerateMatFour());
				render->RenderModel(testObject.shader, testObject.GenerateMatFourForMesh(i), testObject.model.meshes[i]);
			}

			//Skybox

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