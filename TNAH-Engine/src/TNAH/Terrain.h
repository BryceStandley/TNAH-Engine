#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ctime>
#include <cmath>
#include <reactphysics3d/reactphysics3d.h>
#if _WIN32_
#include <math.h>
#include <corecrt_math_defines.h>
#endif

#include "Shader.h"
#include "TextureLoader.h"
#include "Input.h"

#include "BoundingBox.h"



	/**
	 * @class Terrain
	 * @brief Terrain class that loads in a heightmap and generates terrain from it
	 *
	 * @author Dylan Blereau
	 * @version 01
	 * @date 10/03/2021 Dylan Blereau, Started
	 *
	 * @todo break down generateTerrain function
	 * @bugs nothing major currently
	 * 
	 * @authors Dylan Blereau, Bryce Standley
	 * @version 03
	 * @date 02/04/2021 Dylan Blereau, Started
	 * @date MAY 2021 Bryce Standley, improvements
	 * 
	 * @brief added scripting and fixed generateTerrain
	 * @bugs none currently
	 *
	 *
	 * 
	 **/

#define TERRAIN_ERROR_INVALID_PARAM		-5
#define TERRAIN_ERROR_LOADING_IMAGE		-4
#define TERRAIN_ERROR_MEMORY_PROBLEM	-3
#define	TERRAIN_ERROR_NOT_SAVED			-2
#define TERRAIN_ERROR_NOT_INITIALISED	-1
#define TERRAIN_OK						 0

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

		/// struct containing vectors that will hold specific vertex data
	struct Vertex
	{
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> color;
		std::vector<glm::vec3> texture;
		std::vector<glm::vec3> normal;
	};
	
		///the size of the heightfield along x and z - power of 2
	int size;
	int sizeX;
	int sizeZ;
	std::vector<float> terrainHeights;
	int smoothingPasses = 1;
	float MAX_PIXEL_COLOUR = 256 * 256 * 256;
	float MAX_HEIGHT = 40.0f;
	std::vector<unsigned int> texIds;
	Shader shader;
	float minHeight = 0.0f;
	float maxHeight = 0.0f;
	TextureLoader t;
	bool wireFlag = false;
	std::vector<unsigned int> Indices;
	Vertex vertex{};
	std::vector<glm::vec3> totalData;
	std::string filename;
	std::string tex1, tex2, tex3, tex4, tex5;
	glm::vec3 highestPoint = glm::vec3(0,0,0);
	glm::vec3 lowestPoint = glm::vec3(1000,1000,1000);
	BoundingBox::CollisionTag tag;

public:

	rp3d::CollisionBody* terrainCB;
	rp3d::RigidBody* terrainRB;
	rp3d::Collider* terrainCollider;
	float* terrainColliderHeightData;

	glm::vec3 GetMaxHeight(){ return highestPoint; }
	glm::vec3 GetMinHeight(){ return lowestPoint; }
	std::vector<float> GetTerrainHeights();
	
		/**
		* @brief gets and returns a vector containing all indice values
		* @returns std::vector<unsigned int>
		*/
	std::vector<unsigned int> GetIndicies() { return Indices; }

	void SetCollisionTag(BoundingBox::CollisionTag t){tag = t;}
	BoundingBox::CollisionTag* GetTag(){return &tag;}

	std::vector<glm::vec3> GetVertexPositions() { return vertex.position;}
	
		/**
		* @brief gets and returns and vector containing the totalData
		* @returns std::vector<glm::vec3>
		*/
	std::vector<glm::vec3> GetTotalData() { return totalData; }

		/**
		* @brief sets the terrain shader to the shader provided to the function as a parameter
		* @param s - the shader object
		*/
	void SetShader(Shader s) { shader = s; }
	
		/**
		* @brief  default constructor that initialises the terrain object
		*/
	Terrain();
	
		/**
		* @brief  destructor that deallocates terrain memory when object is detroyed
		*/
	~Terrain();

	unsigned int VAO = 0, VBO = 0, EBO = 0;

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
		* @brief A function that calls all the functions required to initialise the terrain
		*/
	void Init();

		/**
		* @brief loads an instance of lua and uses it to assign values from a lua script to terrain variables
		*/
	void luaLoader();

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
	int GetIndicesSize() const { return (int)Indices.size(); }

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
	float getHeightColor(int xpos, int zpos);

		/**
		* @brief Checks if x and y coordinates are within the required range
		* @param x - represents the position on the x-axis
		* @param y - represents the position on the z-axis
		* @return bool
		*/
	bool inBounds(int x, int y);

		/**
		* @brief Generates the terrain by generating the positions, colors, texture coords, indices and placing them in a vector
		*/
	void generateTerrain();

		/**
		* @brief Sets the textures that the terrain will use to implement multitexturing and detail mapping
		*
		*/
	void setTextures();
		
		/**
		*
		* @brief gets and returns the average height around a given x and z point
		* @author Bryce Standley
		* @date   April 2021
		* @param xpos
		* @param zpos
		* @return float
		*/
	float getAverageHeight(int xpos, int zpos);

		/**
		* @brief Generates position vertices
		* @param &vertex - reference to a vertex object
		*/
	void generateVertices(Vertex& vertex);

	/**
	 * @brief Smooths out the terrain data to remove all roughness
	 * @param vert
	 */
	void SmoothTerrain(Vertex& vert, float smoothFactor);

	/**
	 * @brief Interpolates between two float values using Cosine interpolation
	 * @param a
	 * @param b
	 * @param blend
	 * @return interpolated output between a and b using blend factor
	 */
	float Interpolate(float a, float b, float blend);

	glm::vec3 GetScales() {return glm::vec3(scaleX, scaleY, scaleZ);}

	/**
	 * @brief Sets the height of a given position on the terrain
	 * @param xPos
	 * @param zPos
	 * @param newHeight
	 */
	void SetVertexHeight(int xPos, int zPos, float newHeight);

	/**
	 * @brief Gets the final height value of the terrain at a set x,z position
	 * @param xPos
	 * @param zPos
	 * @return float y value
	 */
	float GetVertexHeight(int xPos, int zPos);

		/**
		* @brief Generates indices
		* @param &indices - reference to a vector of unsigned ints
		*/
	void generateIndices(std::vector<unsigned int>& indices);

		/**
		* @brief Generates color vertices
		* @param &vertex - reference to a vertex object
		*/
	void generateColors(Vertex& vertex);

		/**
		* @brief Generates texture vertices
		* @param &vertex - reference to a vertex object
		*/
	void generateTextures(Vertex& vertex);


		/**
		* @brief Generates vertex normals 
		*/
	void generateNormals();
};
#endif //TERRAIN_H

