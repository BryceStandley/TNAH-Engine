#include <glad/glad.h>
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
	virtual void SetBufferFloat(const float* vPos, int vPosCount){}
	virtual void SetBufferVectorFloat(std::vector<float> vPos, int vPosCount){}
	virtual void SetBufferVec3(std::vector<glm::vec3> vPos, std::vector<int> indices){}
	virtual void Terminate() {}
};

