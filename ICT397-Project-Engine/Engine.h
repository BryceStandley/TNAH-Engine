#pragma once
#include "Windows.h"
#include "Scene.h"
#include <vector>
class Engine
{
public:
	Engine();
	~Engine();
	void Run();
private:
	Window* window;
	std::vector<Scene> gameScenes;
	//Renderer
	int currentScene;
	bool running;
};

