#pragma once
#include <GLFW/glfw3.h>
#include "Input.h"
class GlewInput : public Input
{
public:
	GlewInput(GLFWwindow* win)
	{
		window = win;
	}
	bool KeyPress(GLFWwindow* win, int key);
private:
	GLFWwindow* window;
};

