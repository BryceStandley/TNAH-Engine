#pragma once
#include <string>
#include "Terrain.h"
#include "Input.h"
class Window
{
public:
	virtual bool Init(std::string title, int h, int w) { return false; }
	virtual void Buffer() = 0;
	virtual bool GameInput() { return false; }
	virtual void Terminate() {}
	virtual void Clear() {}
	virtual void FrameBuffer() {}
	virtual void Projection(Terrain *gameTerrain) {}

private:
	Input gameInput;	
	Terrain *t;
};

