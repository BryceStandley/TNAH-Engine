#pragma once

#include "Structures.h"

namespace tnah {
	
	/**
	 * @class Submesh
	 *
	 * @brief Sub data class for each submesh within a Model.
	 *
	 * @author Bryce Standley
	 * @date 15/09/2021
	 * 
	 */
	class Submesh
	{
	public:

		/**
		 * @fn Submesh::Submesh() = default;
		 * 
		 * @brief Default constructor of Submesh with empty data.
		 *
		 * @author Bryce Standley
		 * @date 15/09/2021
		 */
		Submesh() = default;

		/**
		* @fn Submesh::Submesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Material>>& materials);
		*
		* @brief Constructor of a Submesh with data.
		*
		* @author Bryce Standley
		* @date 15/09/2021
		*
		* @param vertices A vector of Vertex information of the Submesh.
		* @param indices A vector of indices information of the Submesh.
		* @param materials A vector of Material reference's used by the Submesh.
		* @param transformation A 4x4 matrix of the Submesh in relation to the parent.
		*/
		Submesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Material>>& materials, const glm::mat4& transformation);

		/**
		* @fn std::vector<Vertex>& Submesh::GetVertices() { return m_Vertices; }
		* 
		* @brief Gets the vector of Vertex information of the Submesh.
		*
		* @author Bryce Standley
		* @date 15/09/2021
		*
		* @return Vector of Vertex data.
		*/
		std::vector<Vertex>& GetVertices() { return m_Vertices; }

		/**
		* @fn std::vector<uint32_t>& Submesh::GetIndices() { return m_Indices; }
		* 
		* @brief Gets the index information of the Submesh.
		*
		* @author Bryce Standley
		* @date 15/09/2021
		*
		* @return Vector of index data as 32bit int's.
		*/
		std::vector<uint32_t>& GetIndices() { return m_Indices; }

		/**
		* @fn std::vector<Ref<Material>>& Submesh::GetMaterials() { return m_Materials; }
		* 
		* @brief Gets the material references used by the Submesh.
		*
		* @author Bryce Standley
		* @date 15/09/2021
		*
		* @return Vector of Materials with attached shaders and textures.
		*/
		std::vector<Ref<Material>>& GetMaterials() { return m_Materials; }

		/**
		* @fnglm::mat4& Submesh::GetTransformation() { return m_Transformation; }
		* 
		* @brief Gets the transform relative to the parent.
		*
		* @author Bryce Standley
		* @date 15/09/2021
		*
		* @return 4x4 Transformation matrix
		*/
		glm::mat4& GetTransformation() { return m_Transformation; }

	private:
		/** @brief Vector of vertices within the submesh*/
		std::vector<Vertex> m_Vertices;

		/** @brief Vector of indices within the submesh*/
		std::vector<uint32_t> m_Indices;
		
		/** @brief Vector of materials used within the submesh*/
		std::vector<Ref<Material>> m_Materials = {};

		/** @brief Transform of the submesh compared to the parent*/
		glm::mat4 m_Transformation = {};
	};
}
