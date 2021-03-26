#pragma once
#include <string>
#include "Terrain.h"
#include "Input.h"
class Window
{
public:
	virtual void Init(std::string title, int h, int w) { }
	virtual void Buffer() = 0;
	virtual bool GameInput() { return false; }
	virtual void Terminate() {}
	virtual void Clear() {}
	virtual void FrameBuffer() {}
	virtual void Projection() {}
	virtual void SetShader(Shader shader) {}
	virtual void Restart() {}

private:
	Input gameInput;	
	Terrain *t;
};

