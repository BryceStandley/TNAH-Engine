#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#include "shader.h"
#include "TextureLoader.h"



class Terrain
{

protected:
	unsigned char* terrainData; //data of the heightfield
	float scaleX;
	float scaleY;
	float scaleZ;
	std::string filename;
	std::string tex1, tex2, tex3, tex4, tex5;

private:

	struct Vertex
	{
		std::vector<glm::vec3> position = {};
		std::vector<glm::vec3> color = {};
		std::vector<glm::vec3> texture = {};
		std::vector<glm::vec3> normal = {};
	};

	int size; //the size of the heightfield along x and z - power of 2
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	std::vector<unsigned int> texIds;
	Shader shader;
	float minHeight = 0.0f;
	float maxHeight = 0.0f;
	TextureLoader t;
	bool wireFlag = false;
	std::vector<unsigned int> Indices = {};
	Vertex vertex{};
	std::vector<glm::vec3> totalData = {};

public:

	


	Terrain();
	~Terrain();
	unsigned int GetVAO() const { return VAO; }
	std::vector<unsigned int> GetTextIds() { return texIds; }
	Shader GetShader() const { return shader; }
	void Init();
	void luaLoader();
	void attachShader(Shader shad);
	bool LoadHeightField(std::string filename, int size);
	void setScalingFactor(float xScale, float yScale, float zScale);
	int getSize();
	int GetIndicesSize() const { return Indices.size(); }
	float getHeight(int xpos, int zpos);
	unsigned char getHeightColor(int xpos, int zpos);
	bool inBounds(int x, int y);
	void generateTerrain();
	void modelSetup();
	void setTextures();
	float getAverageHeight(int xpos, int zpos);

	void generateVertices(Vertex& vertex);
	void generateIndices(std::vector<unsigned int>& indices);
	void generateColors(Vertex& vertex);
	void generateTextures(Vertex& vertex);
	void generateNormals(std::vector<unsigned int>& indices);
};

