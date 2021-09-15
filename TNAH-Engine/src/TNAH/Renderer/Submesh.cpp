#include "tnahpch.h"
#include "Submesh.h"

namespace tnah {


	Submesh::Submesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices,
		const std::vector<Ref<Material>>& materials,  const glm::mat4& transformation)
			:m_Vertices(vertices), m_Indices(indices), m_Materials(materials), m_Transformation(transformation)
	{}
	
}
