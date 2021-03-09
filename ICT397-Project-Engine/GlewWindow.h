#pragma once
#include <GLFW/glfw3.h>
#include "Window.h"
class GlewWindow : public Window
{
public:
	GlewWindow() {}
	~GlewWindow() { Terminate(); }
	virtual bool Init(std::string title, int h, int w);
	virtual void Buffer();
	virtual bool GameInput();
	virtual void Terminate();
private:
	Input gameInput;
	GLFWwindow* gameWindow = NULL;
};

