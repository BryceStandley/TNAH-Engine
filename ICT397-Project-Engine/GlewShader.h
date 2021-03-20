#pragma once
#include "Shader.h"
class GlewShader : public Shader
{
public:
	GlewShader(const char* vertPath, const char* fragPath);
	~GlewShader();

	virtual bool Works();
	virtual void Start();
private:
	int program;
	bool error = false;
	int LoadCompileShader(const char* path, int type);
	bool Compild(int shader);
	bool ProgramLinked(int shader);
};

