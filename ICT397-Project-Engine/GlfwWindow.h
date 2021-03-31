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
	virtual bool GameInput();
	virtual void Terminate();
	virtual void Clear();
	virtual void FrameBuffer();
	virtual void Projection();
	virtual void SetShader(Shader shader);
	virtual void SetShaderSkybox(Shader shader);
	virtual void SetShaderTerrain(Shader shader);
	virtual void Restart();

private:
	Input gameInput;
	GLFWwindow* gameWindow = NULL;
	glm::vec3 lightPos;
	Camera camera;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
};

