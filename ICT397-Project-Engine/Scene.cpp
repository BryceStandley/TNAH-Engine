#include "Scene.h"
Scene::Scene(std::string name, std::string fs, std::string vs, std::string t)
{
	this->sceneName = name;

	if (!Init(fs, vs, t))
	{
		std::cout << "SHADER::ERROR::INIT" << std::endl;
	}
}


Scene::~Scene()
{

}

void Scene::Run(View lens)
{
	//Terrain
	gameRenderer->SetShader(gameTerrain->GetShader(), lens);
	gameRenderer->BindTexture(gameTerrain->GetTextIds());
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

bool Scene::Init(std::string fs, std::string vs, std::string t)
{
	gameTerrain = new Terrain();
	Shader s(vs.c_str(), fs.c_str());
	gameTerrain->attachShader(s);
	gameTerrain->Init();	
	gameTerrain->setTextures();

	gameTerrain->generateTerrain();
	gameSkybox = new Skybox("./res/images/skybox/right.jpg", "./res/images/skybox/left.jpg", "./res/images/skybox/top.jpg", "./res/images/skybox/bottom.jpg", "./res/images/skybox/front.jpg", "./res/images/skybox/back.jpg", "./res/shader/skybox_vert.txt", "./res/shader/skybox_frag.txt");
    return true;
}

void Scene::SetupTerrain()
{
	factory = new GameAssetFactory(gameRenderer);
	Player p;
	player = p;
	GameObject* g;
	g = factory->GetGameObject(TypeToken, "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(50, 2, 50), true);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypeToken, "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(50, 2, 50), true);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypeToken, "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(40, 2, 40), true);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypeStatic, "./res/models/environment/Red_Tree.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(30, 2, 30), false);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypeEnemy, "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(60, 2, 50), false);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypeStatic, "./res/models/tree/pine.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(70, 2, 50), false);
	gameObjects.push_back(g);
	g = factory->GetGameObject(TypePlayer, "", "", "", 1, glm::vec3(0, 0, 0), false);
	gameObjects.push_back(g);
	
	gameRenderer->TerrainSetup(gameTerrain->GetTotalData(), gameTerrain->GetIndicies(), gameTerrain->VAO, gameTerrain->VBO, gameTerrain->EBO);
	gameRenderer->SkyboxSetup(gameSkybox->GetSkyVerts(), gameSkybox->GetCubeFaces(), gameSkybox->VAO, gameSkybox->VBO, gameSkybox->texture, gameSkybox->skyShader);

	for (int x = 0; x < gameObjects.size(); x++)
	{
		if (gameObjects[x]->GetType() == "player")
		{
			std::cout << "found player " << x << std::endl;
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
	std::cout << "POS XYZ : " << gameObjects[playerInd]->GetPos().x << " - " << gameObjects[playerInd]->GetPos().y << " - " << gameObjects[playerInd]->GetPos().z << std::endl;
	gameObjects[playerInd]->SetPos(pos);
}

GameObject* Scene::MakeGameObject(std::string modelName, std::string shaderV, std::string shaderF, float s, glm::vec3 p, bool rotate)
{
	Shader ourShader(shaderV.c_str(), shaderF.c_str());
	Model ourModel(modelName, gameRenderer);
	GameObject * obj = new Enemy();
	obj->model = ourModel;
	obj->shader = ourShader;
	obj->SetPos(glm::vec3(p));
	obj->SetScale(s);
	obj->rotate = rotate;

	return obj;
}