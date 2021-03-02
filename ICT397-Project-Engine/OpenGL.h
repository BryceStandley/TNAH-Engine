#pragma once
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <iostream>

class OpenGL : public Renderer
{
public:
	void Render();
	bool Init();
	void Update();
	void Terminate();
	GLFWwindow* window;
private:
	GLclampf red = 0.0f;
	GLclampf green = 0.0f;
	GLclampf blue = 0.0f;
	GLclampf alpha = 1.0f;
	float x = -1.0f;
};

