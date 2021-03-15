#include <gl/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const float * vPos, int vPosCount);
	VertexBuffer(std::vector<float> vPos, int vPosCount);
	VertexBuffer(std::vector<glm::vec3> vPos, std::vector<int> indices);
	~VertexBuffer();
	void Render();
private:
	int vertCount;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};

