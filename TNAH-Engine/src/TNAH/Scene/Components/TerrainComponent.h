#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>
namespace tnah {

	/**********************************************************************************************//**
	 * @struct	Terrain
	 *
	 * @brief	A terrain component that constructs and builds a height map terrain from a provided
	 * 			heightmap file or procedural generation of the height field. Typically used with a
	 * 			HeightMeshCollider to allow collisions with the terrain.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct Terrain 
	{
		glm::vec3 Size;

		Terrain() = default;
		Terrain(const Terrain&) = default;

	};



}