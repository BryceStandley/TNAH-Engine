#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#pragma once
class Shader
{
public:
	Shader() {}
	Shader(const char* vertPath, const char* fragPath) {}
	~Shader();

	virtual bool Works() { return false; }
	virtual void Start(){}
};

