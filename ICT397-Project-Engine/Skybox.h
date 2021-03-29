#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Shader.h"

class Skybox
{
public:
	Skybox() {};
	~Skybox() { Terminate(); };
	virtual void Init(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back, std::string vertexShader, std::string fragmentShader) = 0;
	virtual unsigned int loadCubemap(std::vector<std::string> faces) = 0;
	virtual void Terminate() = 0;
	virtual unsigned int GetVAO() const = 0;
	virtual Shader GetShader() const = 0;
	virtual unsigned int GetTexture() const = 0;

protected:
	Shader skyShader;
};

