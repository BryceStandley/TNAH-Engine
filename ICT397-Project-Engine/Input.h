#pragma once
#include <GLFW/glfw3.h>
#include <string>

#include "luaManager.h"
class Input
{
public:
	Input()
	{
		foward = GLFW_KEY_W;
		back = GLFW_KEY_S;
		left = GLFW_KEY_A;
		right = GLFW_KEY_D;
		wireOn = GLFW_KEY_UP;
		wireOff = GLFW_KEY_DOWN;
		exit = GLFW_KEY_ESCAPE;
	;}

	int foward;
	int back;
	int left;
	int right;
	int wireOn;
	int wireOff;
	int exit;
};

