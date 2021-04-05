#include "Scene.h"
Scene::Scene(std::string name, Renderer * render)
{
	this->sceneName = name;
	gameRenderer = render;

	Init();
}


Scene::~Scene()
{
	delete[]gameRenderer;
	delete[]gameTerrain;
	delete[]gameSkybox;
	for (int i = gameObjects.size()-1; i > 0; i--)
		delete[]gameObjects[i];
	delete[]factory;
}

void Scene::Run(View lens)
{
	//Terrain
	gameRenderer->BindTexture(gameTerrain->GetTextIds());
	Shader t = gameTerrain->GetShader();
	gameRenderer->SetShaderTerrain(t, lens);
	gameTerrain->SetShader(t);
	gameRenderer->RenderTerrain(gameTerrain->GetVAO(), gameTerrain->GetIndicesSize());

	//Skybox
	gameRenderer->SetShaderSkybox(gameSkybox->skyShader, lens);
	gameRenderer->RenderSkybox(gameSkybox->VAO, gameSkybox->texture);

	//Models
	for (int x = 0; x < gameObjects.size(); x++)
	{
		gameObjects[x]->Update(0.1);
		if (x != playerInd)
		{
			gameRenderer->SetShader(gameObjects[x]->shader, lens);
			for (int i = 0; i < gameObjects[x]->model.meshes.size(); i++)
			{
				gameRenderer->RenderModel(gameObjects[x]->shader, gameObjects[x]->GenerateMatFourForMesh(i), gameObjects[x]->model.meshes[i]);
			}
		}
	}

	//If game object is of type player
	UpdatePlayer(lens.GetPosition());
}

void Scene::Init()
{
	gameTerrain = new Terrain();
	gameTerrain->Init();	
	gameTerrain->setTextures();

	gameTerrain->generateTerrain();
	gameSkybox = new Skybox();
	//gameSkybox = new Skybox("./res/images/skybox/right.jpg", "./res/images/skybox/left.jpg", "./res/images/skybox/top.jpg", "./res/images/skybox/bottom.jpg", "./res/images/skybox/front.jpg", "./res/images/skybox/back.jpg", "./res/shader/skybox_vert.txt", "./res/shader/skybox_frag.txt");
	factory = new GameAssetFactory(gameRenderer);
	gameRenderer->TerrainSetup(gameTerrain->GetTotalData(), gameTerrain->GetIndicies(), gameTerrain->VAO, gameTerrain->VBO, gameTerrain->EBO);
	gameRenderer->SkyboxSetup(gameSkybox->GetSkyVerts(), gameSkybox->GetCubeFaces(), gameSkybox->VAO, gameSkybox->VBO, gameSkybox->texture, gameSkybox->skyShader);

	for (int x = 0; x < gameObjects.size(); x++)
	{
		if (gameObjects[x]->GetType() == "player")
		{
			playerInd = x;
			break;
		}
	}
}

void Scene::UpdatePlayer(glm::vec3 position)
{
	glm::vec3 pos = position;
	float worldx, worldz;

	worldx = (pos.x / 100.0f) * (float)gameTerrain->getSize();
	worldz = (pos.z / 100.0f) * (float)gameTerrain->getSize();
	
	pos.y = 1.5f + ((gameTerrain->getAverageHeight(worldx, worldz) / gameTerrain->getSize()) * 100.0f);

	if (gameTerrain->getAverageHeight(worldx, worldz) >= 10.0f)
	{
		pos.x = gameObjects[playerInd]->GetPos().x;
		pos.y = gameObjects[playerInd]->GetPos().y;
		pos.z = gameObjects[playerInd]->GetPos().z;
	}

	gameObjects[playerInd]->SetPos(pos);
}

void Scene::MakeGameObject(std::string t, std::string modelName, std::string shaderV, std::string shaderF, float scale, float x, float y, float z, bool rotate)
{
	GameObject* newGameObject = factory->GetGameObject(t, modelName, shaderV, shaderF, scale, glm::vec3(x, y, z), rotate);
	if (newGameObject != nullptr)
	{
		gameObjects.push_back(newGameObject);
	}
}