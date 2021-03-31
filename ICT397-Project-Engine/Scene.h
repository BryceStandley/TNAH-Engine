#pragma once
#include <string>
#include "GameObjects.h"
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
	GameObject MakeGameObject(std::string modelName, std::string shaderV, std::string shaderF);
	GameObject GetGameObject(int i) { return gameObjects[i]; }
private:
	std::string sceneName;
	GameAssetFactory factory;
	std::vector<GameObject> gameObjects;
	Terrain *gameTerrain;
	Skybox* gameSkybox;
	TextureLoader textureLoader;
};

