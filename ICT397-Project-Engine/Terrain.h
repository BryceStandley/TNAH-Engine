#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TextureLoader.h"
#include "Shader.h"

class Terrain
{

protected:
	unsigned char* terrainData; //data of the heightfield
	float scaleX;
	float scaleY;
	float scaleZ;

private:
	int size; //the size of the heightfield along x and z - power of 2ssssssssss

public:
	typedef struct terrainDataStruct
	{
		std::vector<glm::vec3> vertex;
		std::vector<unsigned int> indices;
		std::vector<glm::vec2> texCoords;

	} terrainDataStruct;

	~Terrain() { delete[] terrainData; }
	
	Shader shader;
	TextureLoader load;
	unsigned int terrainTextureID;

	virtual unsigned int GetVao() { return 1; }
	virtual int GetSize() { return 1; }
	virtual void Render() {};
	virtual void modelSetup() {};
	virtual void generateTerrain() {};
	bool LoadHeightField(std::string filename, int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
	int getSize();
	float getHeight(int xpos, int zpos);
	unsigned char getHeightColor(int xpos, int zpos);
	void setHeightAtPoint(unsigned char height, int xpos, int zpos);
	bool inBounds(int x, int y);
	void addFilter(float* terrainData, float weight);
	bool genFaultFormation(int iter, int hSize, int minHeight, int maxHeight, float weight, bool random);
	void filterPass(float* startP, int increment, float weight);
	void normaliseTerrain(float* terrainData);
};

