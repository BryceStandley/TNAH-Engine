#pragma once
#include <GLFW/glfw3.h>
#include "Renderer.h"
class Input
{
public:
	virtual bool KeyPress(Renderer* r, int key) { return false; }

};

