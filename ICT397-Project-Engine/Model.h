#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include "GlewBuffer.h"
#include "GlewShader.h"

class Model
{
public:
	Model(std::string modelName, std::string vertShader, std::string fragShader);
	~Model();

	VertexBuffer * GetVertexBuffer() const { return buffer; }
	void SetVertexBuffer(VertexBuffer *b) { buffer = b; }

	std::vector<glm::vec3> GetPoints() const { return points; }
	void SetPoints(std::vector<glm::vec3> p) { points = p; }

	Shader * GetShader() const { return shader; }
	void SetShader(Shader * s) { shader = s; }

private:
	VertexBuffer * buffer;
	std::vector<glm::vec3> points;//THis is a place holder, whatever we decide to do in terms of model holding
	Shader * shader;

	bool LoadModel(std::string name);
};

