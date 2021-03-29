#pragma once
#include <iostream>
#include <vector>
class Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size) {}
	virtual void BindTexture(std::vector<unsigned int> textures) {}
	virtual void DepthTest() {}
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture) {}
};

