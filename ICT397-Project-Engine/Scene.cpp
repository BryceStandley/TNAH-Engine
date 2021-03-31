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

void Scene::Run()
{

}

bool Scene::Init(std::string fs, std::string vs, std::string t)
{
	gameTerrain = new Terrain();
	Shader s(vs.c_str(), fs.c_str());
	gameTerrain->attachShader(s);
	gameTerrain->LoadHeightField("test-heightmap.raw", 512);
	gameTerrain->setScalingFactor(1, 3, 1);

	unsigned int grassTexture = textureLoader.loadTexture("grassTile.jpg");
	unsigned int dirtTexture = textureLoader.loadTexture("dirtTile.jpg");
	unsigned int mountainTexture = textureLoader.loadTexture("mountainTile.jpg");
	unsigned int snowTexture = textureLoader.loadTexture("snowTile.jpg");
	unsigned int detailMapTexture = textureLoader.loadTexture("detailMap.jpg");
	gameTerrain->setTextures(grassTexture, dirtTexture, mountainTexture, snowTexture, detailMapTexture);
	gameObjects.push_back(MakeGameObject("res/models/tokens/fbx/Free_Hit.fbx", "res/shader/modelV.glsl", "res/shader/modelF.glsl"));
	gameTerrain->generateTerrain();
	gameTerrain->modelSetup(); 
	gameSkybox = new GladSkybox();
	gameSkybox->Init("./res/images/skybox/right.jpg", "./res/images/skybox/left.jpg", "./res/images/skybox/top.jpg", "./res/images/skybox/bottom.jpg", "./res/images/skybox/front.jpg", "./res/images/skybox/back.jpg", "./res/shader/skybox_vert.txt", "./res/shader/skybox_frag.txt");
    return true;
}

GameObject Scene::MakeGameObject(std::string modelName, std::string shaderV, std::string shaderF)
{
	Shader ourShader(shaderV.c_str(), shaderF.c_str());
	Model ourModel(modelName);
	GameObject obj;
	obj.model = ourModel;
	obj.shader = ourShader;

	return obj;
}