#pragma once
#include "Renderer.h"
class GladRenderer : public Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size);
	virtual void BindTexture(unsigned int texture);
	virtual void DepthTest();
};

