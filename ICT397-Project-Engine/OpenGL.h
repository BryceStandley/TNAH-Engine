#pragma once
#include "Renderer.h"
class OpenGL : public Renderer
{
public:
	virtual void RenderTerrain(unsigned int VAO, int size);
	virtual void RenderModel(Shader& shader, glm::mat4 newModel, Mesh mesh);
	virtual void BindTexture(std::vector<unsigned int> textures);
	virtual void DepthTest();
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture);
	virtual void SetShader(Shader shader, View lens);
	virtual void SetShaderSkybox(Shader shader, View lens);
	virtual void TerrainSetup(std::vector<glm::vec3> totalData, std::vector<unsigned int> Indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	virtual void SkyboxSetup(std::vector <float> skyVerts, std::vector<std::string> faces, unsigned int& VAO, unsigned int& VBO, unsigned int& texture, Shader& skyShader);
	virtual unsigned int TextureFromFile(std::string path, const std::string& directory);
	virtual void SetupMesh(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};

