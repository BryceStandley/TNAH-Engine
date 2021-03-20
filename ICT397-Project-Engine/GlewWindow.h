#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"
#include <iostream>
#include "Callbacks.h"
#include "bruteForce.h"
#include "camera.h"

class GlewWindow : public Window
{
public:
	GlewWindow() {}
	~GlewWindow() { Terminate(); }
	virtual bool Init(std::string title, int h, int w);
	virtual void Buffer();
	virtual bool GameInput();
	virtual void Terminate();
	virtual void Clear();
	virtual void FrameBuffer();
	virtual void Projection(Terrain *gameTerrain);

private:
	Input gameInput;
	GLFWwindow* gameWindow = NULL;
	glm::vec3 lightPos;
	Camera camera;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
};

