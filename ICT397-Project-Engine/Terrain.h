#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#include "shader.h"

typedef struct terrainDataStruct
{
	std::vector<glm::vec3> vertex;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texCoords;

} terrainDataStruct;

class Terrain
{

protected:
	unsigned char* terrainData; //data of the heightfield
	float scaleX;
	float scaleY;
	float scaleZ;

private:
	int size; //the size of the heightfield along x and z - power of 2
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	std::vector<unsigned int> texIds;
	Shader shader;
	float minHeight = 0.0f;
	float maxHeight = 0.0f;

	bool wireFlag = false;

	terrainDataStruct t;

public:


	Terrain();
	~Terrain();
	unsigned int GetVAO() const { return VAO; }
	std::vector<unsigned int> GetTextIds() { return texIds; }
	Shader GetShader() const { return shader; }
	void attachShader(Shader shad);
	bool LoadHeightField(std::string filename, int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
	int getSize();
	int GetIndicesSize() const { return t.indices.size(); }
	float getHeight(int xpos, int zpos);
	unsigned char getHeightColor(int xpos, int zpos);
	bool inBounds(int x, int y);
	void generateTerrain();
	void modelSetup();
	void setTextures(unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4, unsigned int tex5);
	float getAverageHeight(int xpos, int zpos);
};

