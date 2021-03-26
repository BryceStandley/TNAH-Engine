#pragma once
#include <iostream>
class Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size) {}
	virtual void BindTexture(unsigned int texture) {}
	virtual void DepthTest() {}
};

