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


	/**
	 * @class Terrain
	 * @brief Terrain class that loads in a heightmap and generates terrain from it with multitexturing, a detail map and lighting
	 *
	 * @author Dylan Blereau
	 * @version 01
	 * @date 10/03/2021 Dylan Blereau, Started
	 * 
	 * @todo break down generateTerrain function 
	 * @bugs nothing major currently
	 *
	 **/

class Terrain
{

protected:

		///data of the heightfield
	unsigned char* terrainData; 
		/// value that will scale the x value
	float scaleX;
		/// value that will scale the y value
	float scaleY;
		/// value that will scale the z value 
	float scaleZ;	

private:
	
		///the size of the heightfield along x and z - power of 2
	int size; 
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	std::vector<unsigned int> texIds;
	Shader shader;

	bool wireFlag = false;

	terrainDataStruct t;

public:

		/**
		* @brief  default constructor that initialises the terrain object
		*
		*/
	Terrain();

		/**
		* @brief  destructor that deallocates terrain memory when object is detroyed
		* 
		*/
	~Terrain();

		/**
		* @brief Get method that returns the Vertex Array Object
		* @return unsigned int
		*/
	unsigned int GetVAO() const { return VAO; }

		/**
		* @brief Get method that a vector containing texture IDs
		* @return vector<unsigned int>
		*/
	std::vector<unsigned int> GetTextIds() { return texIds; }

		/**
		* @brief Get method that returns a shader object
		* @return Shader
		*/
	Shader GetShader() const { return shader; }

		/**
		* @brief Attaches shader to the terrain
		* @param shad - represents the Shader object that will be attached to the terrain object
		*/
	void attachShader(Shader shad);

		/**
		* @brief loads in a heightmap from a file and places that data into the terrainData variable
		* @param filename - represents the name of the file that the heightmap is being read in from
		* @param size - represents the size of x and z values (if a heightmap is 512x512 size is 512)
		* @return bool
		*/
	bool LoadHeightField(std::string filename, int size);


		/**
		* @brief allows for the individual values of the heightmap to be scaled if needed
		* @param xScale - represents the scaling factor that will be applied to the heightmap on the x-axis
		* @param yScale - represents the scaling factor that will be applied to the heightmap on the y-axis
		* @param zScale - represents the scaling factor that will be applied to the heightmap on the z-axis
		*/
	void setScalingFactor(float xScale, float yScale, float zScale);

		/**
		* @brief Get method that returns the size value 
		* @return int
		*/
	int getSize();

		/**
		* @brief Get method that returns the total size of indices 
		* @return int
		*/
	int GetIndicesSize() const { return t.indices.size(); }

		/**
		* @brief Gets and returns the height (y-value) for a position in the terrain using given x and z values
		* @param xpos - represents the position on the x-axis
		* @param zpos - represents the position on the z-axis
		* @return float
		*/
	float getHeight(int xpos, int zpos);

		/**
		* @brief Gets and returns the height (y-value) color for a position in the terrain using given x and z values
		* @param xpos - represents the position on the x-axis
		* @param zpos - represents the position on the z-axis
		* @return unsigned char
		*/
	unsigned char getHeightColor(int xpos, int zpos);

		/**
		* @brief Checks if x and y coordinates are within the required range
		* @param x - represents the position on the x-axis
		* @param y - represents the position on the z-axis
		* @return bool
		*/
	bool inBounds(int x, int y);

		/**
		* @brief Generates the terrain by generating the positions, colors, texture coords, indices and placing them in a vector
		*
		*/
	void generateTerrain();
		
		/**
		* @brief Readies the model by buffering the vertex data and defining what vertices are for position, colour, texture etc
		*
		*/
	void modelSetup();

		/**
		* @brief Sets the textures that the terrain will use to implement multitexturing and detail mapping
		*
		*/
	void setTextures(unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4, unsigned int tex5);
};

