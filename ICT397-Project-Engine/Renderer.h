#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
class Renderer
{
public:
	Renderer()
	{
		const char* str = glfwGetVersionString();
		std::cout << str << std::endl;
	};
	~Renderer() { Terminate(); }
	virtual void Render() {};
	virtual bool Init() { return false; };
	virtual void Update() {};
	virtual void Terminate() {};
};

