#include "GlewInput.h"

bool GlewInput::KeyPress(GLFWwindow *win, int key)
{
	int state = glfwGetKey(win, key);

	if (state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}
