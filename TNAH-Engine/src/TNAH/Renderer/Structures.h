#pragma once

/**
 * @headerfile Structures.h
 *
 * @brief Different data structures for rendering.
 *
 * @author Bryce Standley
 * @date 15/09/2021
 * 
 */

namespace tnah {

	/**
	 * @struct Vertex
	 *
	 * @brief Structure to hold model vertex information
	 */
	struct Vertex
	{
		/** @brief Position of the vertex*/
		glm::vec3 Position = {};

		/** @brief Normal of the vertex*/
		glm::vec3 Normal = {};

		/** @brief Tangent of the vertex*/
		glm::vec3 Tangent = {};

		/** @brief Binormal (Bitangents) of the vertex*/
		glm::vec3 Binormal = {};

		/** @brief Texture Coordinate of the vertex*/
		glm::vec2 TextureCoordinate = {};

		/** @brief Bone IDs that affect this vertex*/
		glm::ivec4 BoneIDs = {};

		/** @brief Weights of each bone that affect this vertex*/
		glm::vec4 BoneWights = {};

		/**
		 * @fn Vertex::AddBoneData(uint32_t id, float weight);
		 *
		 * @brief Adds bone data to the vertex.
		 *
		 * @param id The id of a bone that affects the vertex.
		 * @param weight The weight of a bone that affects the vertex.
		 * 
		 */
		void AddBoneData(uint32_t id, float weight)
		{
			for (size_t i = 0; i < 4; ++i)
			{
				if (BoneWights[i] == 0.0f)
				{
					BoneIDs[i] = id;
					BoneWights[i] = weight;
					return;
				}
			}
		}
	};



	
}