#pragma once
#include <string>
#include "Input.h"
class Window
{
public:
	~Window() { Terminate(); }
	virtual bool Init(std::string title, int h, int w) { return false; }
	virtual void Buffer() = 0;
	virtual bool GameInput() = 0;
	virtual void Terminate() {}
private:
	Input gameInput;	
};

