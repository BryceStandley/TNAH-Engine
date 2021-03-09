#pragma once
#include <iostream>
#include <fstream>
#include <string>
class Terrain
{
public:
	Terrain()
	{
		sX = 1.0f;
		sY = 1.0f;
		sZ = 1.0f;
		data = NULL;
	}

	~Terrain() { delete [] data; }
	unsigned char* data;
	float sX;
	float sY;
	float sZ;
	bool LoadHeightFeild(std::string filename, int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
private:
	int size;
};

