#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <gl/glew.h>
class Terrain
{
public:
	Terrain()
	{
		sX = 1.0f;
		sY = -1.0f;
		sZ = -1.0f;
		data = NULL;
	}

	~Terrain() { delete [] data; }

	void Render();
	unsigned char* data;
	float sX;
	float sY;
	float sZ;
	bool LoadHeightFeild(std::string filename, int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
	int size;
	float getHeight(int xpos, int zpos);
	bool inBounds(int x, int y);
};

