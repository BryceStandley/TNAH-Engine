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
	gameTerrain = new bruteForce();
	gameTerrain->genFaultFormation(128, 128, 0, 1, 0.3, 1);
	gameTerrain->setScalingFactor(1, 2, 1);
	Shader s(vs.c_str(), fs.c_str());
    gameTerrain->shader = s;
    gameTerrain->terrainTextureID = gameTerrain->load.loadTexture(t.c_str(), "", 0);
	gameTerrain->generateTerrain();
	gameTerrain->modelSetup();

    return true;
}