#pragma once
#include <glad/glad.h>
#include "Windows.h"
#include "Scene.h"
#include "GladRenderer.h"
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
	Renderer * render;
	int currentScene;
	bool running;
};

