#pragma once
#include <glad/glad.h>
#include "Windows.h"
#include "Scene.h"
#include "OpenGL.h"
#include <vector>
class Engine
{
public:
	Engine();
	~Engine();
	void Run();
private:

	void InitiliseScene();

	Window* window;
	std::vector<Scene> gameScenes;
	Renderer * render;
	int currentScene;
	int totalScenes;
	bool running;
};

