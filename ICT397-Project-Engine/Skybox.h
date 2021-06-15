#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Terrain.h"


	/**
	* @class Skybox
	* @brief A class that is responsible for creating a setting up a skybox 
	*
	* @author Dylan Blereau
	* @version 01
	* @date 27/03/2021 Dylan Blereau, Started
	*
	**/
class Skybox
{
public:

		/**
		* @brief default constructor that initialises the object and sets the vertices of the skybox 
		*/
	Skybox();

		/**
		* @brief a constructor that takes in the paths to the images for each face of the skybox, as well as the paths to its vertex and fragment shader
		* 
		* @param right - represents the right face of the skybox
		* @param left - represents the left face of the skybox
		* @param top - represents the top face of the skybox
		* @param bottom - represents the bottom face of the skybox
		* @param front - represents the front face of the skybox
		* @param back - represents the back face of the skybox
		* @param vertexShader - represents the skybox's vertex shader
		* @param fragmentShader - represents the skybox's fragment shader
		*/
	Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back, std::string vertexShader, std::string fragmentShader);

		/**
		* @brief destructor
		*/
	~Skybox() { };

		/// shader object
	Shader skyShader;
	unsigned int VAO = 0, VBO = 0;
	unsigned int texture = 0;

		/**
		* @brief gets and returns all the cubeFaces that make up the skybox
		* @return std::vector<std::string> 
		*/
	std::vector<std::string> GetCubeFaces() { return cubeFaces; }

		/**
		* @brief gets and returns all the vertices that make up the skybox
		* @return std::vector<float>
		*/
	std::vector<float> GetSkyVerts() { return skyVerts; }

private:
		/**
		* @brief sets all vertices required to draw the skybox correctly
		*/
	void SetSkyVerts();

	std::vector<std::string> cubeFaces;
	std::vector<float> skyVerts;
};

