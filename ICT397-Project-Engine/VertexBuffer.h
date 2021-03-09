#include <gl/glew.h>
#include <iostream>
#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const float * vPos, int vPosCount);
	~VertexBuffer();
	void Render();
private:
	int vertCount;
	GLuint VBO;
	GLuint VAO;
};

