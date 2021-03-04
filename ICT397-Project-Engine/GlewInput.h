#pragma once
#include <GLFW/glfw3.h>
#include "Input.h"
#include "OpenGL.h"

class GlewInput : public Input
{
public:
	GlewInput(GLFWwindow* win)
	{
		window = win;
	}
	bool KeyPress(Renderer* r, int key);
private:
	GLFWwindow* window;
};

