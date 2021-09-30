#include "tnahpch.h"
#include "Submesh.h"

namespace tnah {


	Submesh::Submesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices,
		const std::vector<Ref<Material>>& materials,  const glm::mat4& transformation)
			:m_Vertices(vertices), m_Indices(indices), m_Materials(materials), m_Transformation(transformation)
	{
		m_VerticesIndex = m_Vertices.size();
		m_IndicesIndex = m_Indices.size();
	}

	uint32_t Submesh::VerticesIndex() const
	{
		return m_VerticesIndex;
	}

	void Submesh::SetVerticesIndex(uint32_t verticesIndex)
	{
		m_VerticesIndex = verticesIndex;
	}

	uint32_t Submesh::IndicesIndex() const
	{
		return m_IndicesIndex;
	}

	void Submesh::SetIndicesIndex(uint32_t indicesIndex)
	{
		m_IndicesIndex = indicesIndex;
	}

}
