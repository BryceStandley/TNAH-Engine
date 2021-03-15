#pragma once
#include <string>
#include "GameAssetFactory.h"
#include "Terrain.h"
#include <vector>
class Scene
{
public:
	Scene(std::string type);
	~Scene();
	bool Init();

	std::vector<GameObject> GetGameObjects() const { return gameObjects; }
	void SetGameObjects(std::vector<GameObject> g) { gameObjects = g; }

private:
	std::string sceneType;
	GameAssetFactory factory;
	Terrain gameTerrain;
	std::vector<GameObject> gameObjects;
};

