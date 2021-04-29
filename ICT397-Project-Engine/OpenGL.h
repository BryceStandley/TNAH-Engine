#pragma once
#include "Renderer.h"
#include "Debugging.h"
/**
* @class OpenGL
* @brief The abstract OpenGL version of the renderer.
* Uses the Renderer parent class to have an abstract opengl class that doesnt directly intereact with the system
* and is used via facading it into the system.
*
* @author Christoper Logan
* @version 01
* @date 15/03/2021 Christopher Logan, Started
*
*
**/
class OpenGL : public Renderer
{
public:
	/**
	* @brief Renders the games terrain
	* @param VAO - The vertex array object
	* @param size - the size needed to render
	*/
	virtual void RenderTerrain(unsigned int VAO, int size);

	/**
	* @brief Renders the games model
	* @param shader - The objects shader
	* @param newModel - The matrix4 model infromation for rotation or scaling
	* @param The mesh - The current mesh of the object
	*/
	virtual void RenderModel(Shader& shader, glm::mat4 newModel, Mesh mesh);

	/**
	* @brief Binds textures to memory
	* @param textures - The list of textures being used
	*/
	virtual void BindTexture(std::vector<unsigned int> textures);

	/**
	* @brief Calls the depth test
	*/
	virtual void DepthTest();

	/**
	* @brief Renders the sky box
	* @param VAO - The vertex array object
	* @param texture - The texture number
	*/
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture);

	/**
	* @brief Sets the shader and uses it
	* @param shader - The shader used
	* @param lens - The viewing information
	*/
	virtual void SetShader(Shader shader, View lens);

	/**
	* @brief Sets the shader and uses it for the skybox
	* @param shader - The shader used
	* @param lens - The viewing information
	*/
	virtual void SetShaderSkybox(Shader shader, View lens);

	/**
	* @brief Sets up the terrain data
	* @param totalData - The vec3 data information
	* @param indices - The list of positions for the totalData
	* @param VAO - The vertex array object
	* @param VBO - The vertex buffer object
	* @param EBO - Another buffer
	*/
	virtual void TerrainSetup(std::vector<glm::vec3> totalData, std::vector<unsigned int> Indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	/**
	* @brief Sets up the skybox
	* @param skyVerts - The vertice positions
	* @param faces - The texture file names
	* @param VAO - The vertex array object
	* @param VBO - The vertex buffer object
	* @param EBO - Another buffer
	* @param texture - The texture number
	* @param skyShader - The skybox shader
	*/
	virtual void SkyboxSetup(std::vector<float> skyVerts, std::vector<std::string> faces, unsigned int& VAO, unsigned int& VBO, unsigned int& texture, Shader& skyShader);

	/**
	* @brief Sets up the skybox
	* @param path - the path to the texture
	* @param directory - the directory of the file
	* @return unsigned int
	*/
	virtual unsigned int TextureFromFile(std::string path, const std::string& directory);

	/**
	* @brief Sets an objects mesh
	* @param VAO - The vertex array object
	* @param VBO - The vertex buffer object
	* @param EBO - Another buffer
	* @param vertices - The vertex positions for the mesh
	* @param indices - The indice positons
	*/
	virtual void SetupMesh(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	/**
	* @brief Sets up the shader for the terrain
	* @param shader - The shader used
	* @param lens - The viewing information
	*/
	virtual void SetShaderTerrain(Shader& shader, View lens);

	/**
	* @brief Rends the exit model
	* @param VAO - The vertex array object
	* @param texture - The texture number
	* @param EBO - Another buffer
	*/
	virtual void RenderExitScreen(unsigned int VAO, unsigned int EBO, unsigned int texture);

	/**
	* @brief Sets up the exit screen
	* @param vertexData - the positions data
	* @param indices - The indices data
	* @param VAO - The vertex array object
	* @param VBO - The vertex buffer object
	* @param EBO - Another buffer
	*/
	virtual void ExitScreenSetup(std::vector<glm::vec3> vertexData, std::vector<unsigned int> indicesData, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	unsigned int TextureFromFile(std::string path);

	virtual void LoadModelMd2(Buffer& buffer, std::vector<Buffer> &vboBuffers);
    tnah::Debugging debugger;
};

