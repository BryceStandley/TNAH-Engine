#pragma once
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
class Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size) {}
	virtual void RenderModel(Shader& shader, glm::mat4 newModel, Mesh mesh) {}
	virtual void BindTexture(std::vector<unsigned int> textures) {}
	virtual void DepthTest() {}
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture) {}
};

