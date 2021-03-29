#pragma once
#include "Renderer.h"
class GladRenderer : public Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size);
	virtual void BindTexture(std::vector<unsigned int> textures);
	virtual void DepthTest();
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture);
};

