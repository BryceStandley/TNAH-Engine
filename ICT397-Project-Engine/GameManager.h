#pragma once
#include <iostream>
#include "OpenGL.h"
class GameManager
{
public:
	void Print() { std::cout << i << std::endl; }
	int i = 0;
	Renderer *gameRenderer;
};

