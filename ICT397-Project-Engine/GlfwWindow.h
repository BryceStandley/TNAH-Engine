#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"
#include <iostream>
#include "Callbacks.h"

#include "camera.h"
#include "Shader.h"

class GlfwWindow : public Window
{
public:
	GlfwWindow() {}
	~GlfwWindow() { Terminate(); }
	virtual void Init(std::string title, int h, int w);
	virtual void Buffer();
	virtual bool GameInput(float deltaTime);
	virtual void Terminate();

	virtual void FrameBuffer();

	virtual void SetShader(Shader shader);
	virtual void SetShaderSkybox(Shader shader);
	virtual void SetShaderTerrain(Shader shader);
	
	virtual Camera GetCamera() { return camera; }
	virtual void UpdateCamera(glm::vec3 p) { camera.Position = p; }
	virtual void MouseMove();
	virtual View GetLens() { return lens; }
	virtual void Update();
	virtual float GetTime() { return gametime.DeltaTime(); }

private:	
	void Projection();
	void Clear();
	void Restart();
	Input gameInput;
	GLFWwindow* gameWindow = NULL;
	glm::vec3 lightPos;
	Camera camera;
	View lens;
	Time gametime;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	float lastX;
	float lastY;
	float firstMouse = true;
};

