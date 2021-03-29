#pragma once
#include <string>
#include "GameAssetFactory.h"
#include "Terrain.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "camera.h"
#include "GladSkybox.h"

class Scene
{
public:
	Scene(std::string name, std::string fs, std::string vs, std::string t);
	~Scene();
	void Run();
	bool Init(std::string fs, std::string vs, std::string t);
	Terrain *GetTerrain() { return gameTerrain; }
	Skybox* GetSkybox() { return gameSkybox; }
	std::string GetSceneName() const { return sceneName; }
private:
	std::string sceneName;
	GameAssetFactory factory;
	Terrain *gameTerrain;
	Skybox* gameSkybox;
	TextureLoader textureLoader;
};

