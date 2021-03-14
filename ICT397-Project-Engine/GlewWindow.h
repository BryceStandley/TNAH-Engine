#pragma once
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>
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
private:
	Input gameInput;
	GLFWwindow* gameWindow = NULL;
};

