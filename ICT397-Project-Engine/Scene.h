#pragma once
#include <string>
#include "GameAssetFactory.h"
#include "bruteForce.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "camera.h"
class Scene
{
public:
	Scene(std::string name, std::string fs, std::string vs, std::string t);
	~Scene();
	void Run();
	bool Init(std::string fs, std::string vs, std::string t);
	Terrain *GetTerrain() { return gameTerrain; }
private:
	std::string sceneName;
	GameAssetFactory factory;
	Terrain * gameTerrain;
};

