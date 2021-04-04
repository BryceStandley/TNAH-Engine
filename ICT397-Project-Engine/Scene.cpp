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
	gameRenderer->SetShaderSkybox(gameSkybox->GetShader(), lens);
	gameRenderer->RenderSkybox(gameSkybox->GetVAO(), gameSkybox->GetTexture());

	//Models
	for (int x = 0; x < gameObjects.size(); x++)
	{
		gameRenderer->SetShader(gameObjects[x]->shader, lens);
		for (int i = 0; i < gameObjects[x]->model.meshes.size(); i++)
		{
			gameRenderer->RenderModel(gameObjects[x]->shader, gameObjects[x]->GenerateMatFourForMesh(i), gameObjects[x]->model.meshes[i]);
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
	//gameTerrain->LoadHeightField("test-heightmap.raw", 512);
	//gameTerrain->setScalingFactor(1, 3, 1);

	
	gameTerrain->setTextures();
	Player p;
	player = p;
	GameObject* g = MakeGameObject("./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.3, glm::vec3(0,0,0));
	gameObjects.push_back(g);
	g = MakeGameObject("./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(50, 2, 50));
	gameObjects.push_back(g);
	g = MakeGameObject("./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(40, 2, 40));
	gameObjects.push_back(g);
	g = MakeGameObject("./res/models/environment/Red_Tree.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(30, 2, 30));
	gameObjects.push_back(g);
	g = MakeGameObject("./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(60, 2, 50));
	gameObjects.push_back(g);
	g = MakeGameObject("./res/models/tree/pine.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, glm::vec3(70, 2, 50));
	gameObjects.push_back(g);
	gameTerrain->generateTerrain();
	gameTerrain->modelSetup(); 
	gameSkybox = new GladSkybox();
	gameSkybox->Init("./res/images/skybox/right.jpg", "./res/images/skybox/left.jpg", "./res/images/skybox/top.jpg", "./res/images/skybox/bottom.jpg", "./res/images/skybox/front.jpg", "./res/images/skybox/back.jpg", "./res/shader/skybox_vert.txt", "./res/shader/skybox_frag.txt");
    return true;
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
		pos.x = player.GetPos().x;
		pos.y = player.GetPos().y;
		pos.z = player.GetPos().z;
	}

	
	std::cout << "Terrain Height at player position: " << gameTerrain->getAverageHeight(worldx, worldz) << " With Player XYZ: " << pos.x << "  -  " << pos.y << "  -  " << pos.z << std::endl;
	player.SetPos(pos);
}

GameObject* Scene::MakeGameObject(std::string modelName, std::string shaderV, std::string shaderF, float s, glm::vec3 p)
{
	Shader ourShader(shaderV.c_str(), shaderF.c_str());
	Model ourModel(modelName);
	GameObject * obj = new GameObject();
	obj->model = ourModel;
	obj->shader = ourShader;
	obj->SetPos(glm::vec3(p));
	obj->SetScale(s);

	return obj;
}