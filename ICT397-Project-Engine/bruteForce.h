#pragma once
#include <glad/glad.h>
#include "Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class bruteForce : public Terrain
{
public:
	unsigned int GetVao() { return VAO; }
	int GetSize() { return t.indices.size(); }
	void Render();
	void generateTerrain();
	void modelSetup();
	terrainDataStruct t;
	//std::vector<glm::vec3> positions;
	//std::vector<unsigned int> indices;
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	unsigned int texID = 0, texID2 = 0;
	void resetTerrain();
};

