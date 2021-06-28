#pragma once
#include <iostream>
#include <vector>
#include "Md2State.h"
#include "Shader.h"
#include "Mesh.h"
#include "View.h"
#include "Buffer.h"
#include "Debugger.h"
#include "PhysicsManager.h"

typedef float v3[3];
	/**
	* @class Renderer
	* @brief Contains the absract information for the Renderer.
	* The class holds all the functions that would be used to set up models and render them, it does not however provide any functionality
	* and would be used to setup a API, such as OpenGL or directX.
	*
	* @author Christoper Logan
	* @version 01
	* @date 15/03/2021 Christopher Logan, Started
	*
	*
	**/
class Renderer
{
public:

		/**
		* @brief Renders the games terrain
		* @param VAO - The vertex array object
		* @param size - the size needed to render
		*/
	virtual void RenderTerrain(unsigned int VAO, int size) {}

		/**
		* @brief Renders the games model
		* @param shader - The objects shader
		* @param newModel - The matrix4 model infromation for rotation or scaling
		* @param The mesh - The current mesh of the object
		*/
	virtual void RenderModel(Shader& shader, glm::mat4 newModel, Mesh mesh) {}

		/**
		* @brief Binds textures to memory
		* @param textures - The list of textures being used
		*/
	virtual void BindTexture(std::vector<unsigned int> textures) {}

		/**
		* @brief Calls the depth test
		*/
	virtual void DepthTest() {}

		/**
		* @brief Renders the sky box
		* @param VAO - The vertex array object
		* @param texture - The texture number
		*/
	virtual void RenderSkybox(unsigned int VAO, unsigned int texture) {}

		/**
		* @brief Sets the shader and uses it
		* @param shader - The shader used
		* @param lens - The viewing information
		*/
	virtual void SetShader(Shader shader, View lens) {}

		/**
		* @brief Sets the shader and uses it for the skybox
		* @param shader - The shader used
		* @param lens - The viewing information
		*/
	virtual void SetShaderSkybox(Shader shader, View lens) {}

		/**
		* @brief Sets up the terrain data
		* @param totalData - The vec3 data information
		* @param indices - The list of positions for the totalData
		* @param VAO - The vertex array object
		* @param VBO - The vertex buffer object
		* @param EBO - Another buffer
		*/
	virtual void TerrainSetup(std::vector<glm::vec3> totalData, std::vector<unsigned int> Indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {}

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
	virtual void SkyboxSetup(std::vector<float> skyVerts, std::vector<std::string> faces, unsigned int& VAO, unsigned int& VBO, unsigned int &texture, Shader& skyShader) {}

		/**
		* @brief Sets up the skybox
		* @param path - the path to the texture
		* @param directory - the directory of the file
		* @return unsigned int
		*/
	virtual unsigned int TextureFromFile(std::string path, const std::string& directory) { return 0; }

		/**
		* @brief Sets an objects mesh
		* @param VAO - The vertex array object
		* @param VBO - The vertex buffer object
		* @param EBO - Another buffer
		* @param vertices - The vertex positions for the mesh
		* @param indices - The indice positons
		*/
	virtual void SetupMesh(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, std::vector<Vertex> vertices, std::vector<unsigned int> indices) {}

		/**
		* @brief Sets up the shader for the terrain
		* @param shader - The shader used
		* @param lens - The viewing information
		*/
	virtual void SetShaderTerrain(Shader &shader, View lens) {}

		/**
		* @brief Rends the exit model
		* @param VAO - The vertex array object
		* @param texture - The texture number
		* @param EBO - Another buffer
		*/
    virtual void RenderExitScreen(unsigned int VAO, unsigned int EBO, unsigned int texture){};

		/**
		* @brief Sets up the exit screen
		* @param vertexData - the positions data
		* @param indices - The indices data
		* @param VAO - The vertex array object
		* @param VBO - The vertex buffer object
		* @param EBO - Another buffer
		*/
    virtual void ExitScreenSetup(std::vector<glm::vec3> vertexData, std::vector<unsigned int> indicesData, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO){};

	unsigned int TextureFromFile(std::string path) { return 0; }

	virtual int LoadModel(int numFrames, std::vector<int> commands, unsigned int &VAO, v3 anorms[162], std::vector<std::vector<glm::vec3>> vertices, std::vector<std::vector<int>> normals) { return 0; }

	virtual void RenderModel(int number, Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::mat4 genFour, float direction, unsigned int& VAO, unsigned int& textureId, Shader& shader) {}
	virtual void RenderModel(int number, Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 position, glm::vec3 rotation, float direction, unsigned int& VAO, unsigned int& textureId, Shader& shader) {}

	virtual void SetGlfwWindow(){}

	/**
	 * @brief Renders the debug information from the react physics renderer
	 * @param debugRenderer - Debug Renderer object from react with all render information
	 */
	virtual void RenderReactDebugger(rp3d::DebugRenderer debugRenderer, View lens){}

	virtual void SetUpReactDebugger(rp3d::DebugRenderer debugRenderer){}
	virtual void UpdateReactDebugVBO(){}
};

