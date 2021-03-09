#pragma once
#include <GLFW/glfw3.h>
class Input
{
public:
	virtual bool KeyPress(GLFWwindow* win, int key) { return false; }
	virtual bool MouseMove() { return false; }
};

