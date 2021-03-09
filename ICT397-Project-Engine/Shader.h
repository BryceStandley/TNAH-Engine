#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#pragma once
class Shader
{
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	bool Works();
	void Start();
private:
	int program;
	bool error = false;
	int LoadCompileShader(const char * path, int type);
	bool Compild(int shader);
	bool ProgramLinked(int shader);
};

