#pragma once
#include "VertexBuffer.h"
class GlewBuffer : public VertexBuffer
{
public:
	GlewBuffer(const float* vPos, int vPosCount);
	GlewBuffer(std::vector<float> vPos, int vPosCount);
	GlewBuffer(std::vector<glm::vec3> vPos, std::vector<int> indices);

private:
	virtual void SetBufferFloat(const float* vPos, int vPosCount);
	virtual void SetBufferVectorFloat(std::vector<float> vPos, int vPosCount);
	virtual void SetBufferVec3(std::vector<glm::vec3> vPos, std::vector<int> indices);
	virtual void Terminate();
	int vertCount;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

