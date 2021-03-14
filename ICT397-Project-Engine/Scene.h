#pragma once
#include <string>
#include "GameAssetFactory.h"
class Scene
{
public:
	Scene(std::string name);
	~Scene();
	void Run();
	bool Init();
private:
	std::string sceneName;
	GameAssetFactory factory;
};

