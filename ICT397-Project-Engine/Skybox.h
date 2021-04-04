#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Shader.h"

class Skybox
{
public:
	Skybox() { SetSkyVerts(); }
	Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back, std::string vertexShader, std::string fragmentShader);
	~Skybox() { };
	Shader skyShader;
	unsigned int VAO = 0, VBO = 0;
	unsigned int texture = 0;
	std::vector<std::string> GetCubeFaces() { return cubeFaces; }
	std::vector<float> GetSkyVerts() { return skyVerts; }
private:
	void SetSkyVerts();
	std::vector<std::string> cubeFaces;
	std::vector<float> skyVerts;
};

