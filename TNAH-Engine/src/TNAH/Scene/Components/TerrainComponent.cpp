#include "tnahpch.h"
#include "TerrainComponent.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/gtc/type_ptr.hpp>

namespace tnah {

	Terrain::Terrain()
	{
		GenerateHeightmap(100, 100, 40);
		Create();
		m_TerrainVAO.reset(VertexArray::Create());
		m_TerrainVBO.reset(VertexBuffer::Create(m_TerrainVBOData, sizeof(m_TerrainVBOData)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float3, "a_TextureCoord"},
			{ShaderDataType::Float3, "a_Normal"}
		};
		m_TerrainVBO->SetLayout(layout);
		m_TerrainVAO->AddVertexBuffer(m_TerrainVBO);
		m_TerrainVAO->SetIndexBuffer(m_TerrainIBO);
	}

	Terrain::Terrain(const std::string heightmapFilePath)
	{
		if (LoadHeightField(heightmapFilePath))
		{
			Create();
			m_TerrainVAO.reset(VertexArray::Create());
			m_TerrainVBO.reset(VertexBuffer::Create(m_TerrainVBOData, sizeof(m_TerrainVBOData)));
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float3, "a_Color"},
				{ShaderDataType::Float3, "a_TextureCoord"},
				{ShaderDataType::Float3, "a_Normal"}
			};
			m_TerrainVBO->SetLayout(layout);
			m_TerrainVAO->AddVertexBuffer(m_TerrainVBO);
			m_TerrainVAO->SetIndexBuffer(m_TerrainIBO);
		}
	}

	Terrain::Terrain(const int width, const int maxHeight, const int minHeight)
	{
		GenerateHeightmap(width, maxHeight, minHeight);
		Create();
		m_TerrainVAO.reset(VertexArray::Create());
		m_TerrainVBO.reset(VertexBuffer::Create(m_TerrainVBOData, sizeof(m_TerrainVBOData)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float3, "a_TextureCoord"},
			{ShaderDataType::Float3, "a_Normal"}
		};
		m_TerrainVBO->SetLayout(layout);
		m_TerrainVAO->AddVertexBuffer(m_TerrainVBO);
		m_TerrainVAO->SetIndexBuffer(m_TerrainIBO);
	}

	Terrain::~Terrain()
	{
		TNAH_CORE_ERROR("Terrain deconstructor called");
		//delete[] m_TerrainVBOData;
		//m_TerrainIBO->Delete();
		//m_TerrainVBO->Delete();
		//m_TerrainVAO->Delete();
	}

	void Terrain::Create()
	{
		GenerateVertexPositions(m_TerrainInfo);
		SmoothTerrain(m_TerrainInfo);
		GenerateVertexColors(m_TerrainInfo);
		GenerateVertexTextureCoords(m_TerrainInfo);
		GenerateVertexIndices(m_TerrainIBO);
		GenerateVertexNormals(m_TerrainInfo);

		m_TerrainVBOData = static_cast<float*>(malloc(m_TerrainInfo.position.size() * (sizeof(float) * 12)));

		int k = 0;
		for (int i = 0; i < m_TerrainInfo.position.size(); ++i)
		{
			m_TerrainVBOData[k]      = m_TerrainInfo.position[i].x;
			m_TerrainVBOData[k + 1]  = m_TerrainInfo.position[i].y;
			m_TerrainVBOData[k + 2]  = m_TerrainInfo.position[i].z;

			m_TerrainVBOData[k + 3]  = m_TerrainInfo.color[i].x;
			m_TerrainVBOData[k + 4]  = m_TerrainInfo.color[i].y;
			m_TerrainVBOData[k + 5]  = m_TerrainInfo.color[i].z;

			m_TerrainVBOData[k + 6]  = m_TerrainInfo.texture[i].x;
			m_TerrainVBOData[k + 7]  = m_TerrainInfo.texture[i].y;
			m_TerrainVBOData[k + 8]  = m_TerrainInfo.texture[i].z;

			m_TerrainVBOData[k + 9]  = -m_TerrainInfo.normal[i].x;
			m_TerrainVBOData[k + 10] = -m_TerrainInfo.normal[i].y;
			m_TerrainVBOData[k + 11] = -m_TerrainInfo.normal[i].z;
			k += 12;
			/*
			m_TerrainVBOData.emplace_back(m_TerrainInfo.position[i]);
			m_TerrainVBOData.emplace_back(m_TerrainInfo.color[i]);
			m_TerrainVBOData.emplace_back(m_TerrainInfo.texture[i]);
			m_TerrainVBOData.emplace_back(-m_TerrainInfo.normal[i]);
			*/
		}
	}

	void Terrain::GenerateHeightmap(const int width, const int maxHeight, const int minHeight)
	{
		//TODO: Add some math here to generate a height map using noise
		// use nested for loop of x and z using m_Size.x as a limit
		// push the height value into m_TerrainHeights[z * m_Size.x + x]
	}

	bool Terrain::LoadHeightField(const std::string& fileName)
	{
		stbi_set_flip_vertically_on_load(1);
		int width, height, bytesPerPixel;
		const auto imageData = stbi_load(fileName.c_str(), &width, &height, &bytesPerPixel, 0);
		if (imageData == nullptr)
		{
			// Return empty vector in case of failure
			TNAH_CORE_ASSERT(false, "Failed to load provided heightmap image file!");
		}

		std::vector<float> result;
		auto pixelPtr = &imageData[0];
		for (auto z = 0; z < height; ++z)
		{
			for (auto x = 0; x < width; ++x)
			{
				result.emplace_back((float(*pixelPtr) / 255.0f) * m_MaxHeightmapHeight);
				pixelPtr += bytesPerPixel;
			}
		}

		stbi_image_free(imageData);
		m_TerrainHeights = result;
		m_Size.x = width;
		m_Size.y = height;
		stbi_set_flip_vertically_on_load(0);
		return true;
	}

	const float Terrain::GetHeight(int x, int z)
	{
		if (x < 0) { x = 0; }
		if (z < 0) { z = 0; }
		if (x > m_Size.x) { x = m_Size.x; }
		if (z > m_Size.x) { z = m_Size.x; }
		if (InBounds(x, z))
		{
			return m_TerrainHeights[z * (int)m_Size.x + x];
		}
		else
		{
			return m_TerrainHeights[((z - 1) * (int)m_Size.x) + x];
		}
	}

	const float Terrain::GetHeightColor(int x, int z)
	{
		if (InBounds(x, z)) {
			return m_TerrainHeights[(z * (int)m_Size.x) + x];
		}
		return 1;
	}

	const float Terrain::GetVertexHeight(int x, int z)
	{
		if (x < 0) { x = 0; }
		if (z < 0) { z = 0; }
		if (x >= m_Size.x) { x = m_Size.x - 1; }
		if (z >= m_Size.x) { z = m_Size.x - 1 ; }
		if (InBounds(x, z))
		{
			return m_TerrainInfo.position[z * (int)m_Size.x + x].y;
		}
		else
		{
			return m_TerrainInfo.position[((z - 1) * (int)m_Size.x) + x].y;
		}
	}

	bool Terrain::InBounds(int x, int z)
	{
		if ((x >= 0 && (float)x < m_Size.x) && (z >= 0 && z < m_Size.x ))
			return true;
		else
			return false;
	}

	void Terrain::SetVertexHeight(int x, int z, const float newHeight)
	{
		if (InBounds(x, z))
			m_TerrainInfo.position[(z * (int)m_Size.x) + x].y = newHeight;
		else
			m_TerrainInfo.position[(z - 1 * (int)m_Size.x) + x].y = newHeight;
	}

	void Terrain::GenerateVertexPositions(TerrainInformation& terrainInformation)
	{
		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				glm::vec3 positions((float)x, GetHeight(x, z), (float)z);
				m_TerrainInfo.position.push_back(positions);
				if (positions.y > m_HighestPoint.y) { m_HighestPoint = glm::vec3(x, positions.y, z); }
				if (positions.y < m_LowestPoint.y) { m_LowestPoint = glm::vec3(x, positions.y, z); }
			}
		}
	}

	void Terrain::GenerateVertexIndices(Ref<IndexBuffer>& IBO)
	{
		std::vector<uint32_t> indices;
		for (unsigned int z = 0; z < m_Size.x - 1; ++z)
		{
			for (unsigned int x = 0; x < m_Size.x - 1; ++x) {
				indices.push_back((x * m_Size.x + z));             // 0
				indices.push_back(((x * m_Size.x + 1) + z));       // 1
				indices.push_back((((x + 1) * m_Size.x) + z));     // 3

				indices.push_back(((x * m_Size.x + 1) + z));       // 1
				indices.push_back(((x + 1) * m_Size.x) + (z + 1)); // 2
				indices.push_back((((x + 1) * m_Size.x) + z));     // 3
			}
		}
		m_Indices = static_cast<uint32_t*>(malloc(indices.size() * sizeof(uint32_t)));
		for (int i = 0; i < indices.size(); i++)
		{
			m_Indices[i] = indices[i];
		}
		
		IBO.reset(IndexBuffer::Create(m_Indices, sizeof(m_Indices)));
	}

	void Terrain::GenerateVertexColors(TerrainInformation& terrainInformaion)
	{
		float colorVal = 0.0f;

		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				colorVal = GetVertexHeight(x, z) / 255.0f;
				glm::vec3 color(0.0f, colorVal, 0.0f);
				m_TerrainInfo.color.emplace_back(color);
			}
		}
	}

	void Terrain::GenerateVertexTextureCoords(TerrainInformation& terrainInformation)
	{
		unsigned int tracker = 0;
		float prevx = m_TerrainInfo.position[0].x;
		int s = 1;
		int x = 0;
		int z = 0;
		glm::vec3 texCoords = glm::vec3(0.0f);
		for (auto& vert : m_TerrainInfo.position)
		{
			if (static_cast<int>(prevx) != static_cast<int>(vert.x))
			{
				x++;
				z = 0;
				prevx = vert.x;
			}
			if (tracker == 0)
			{
				texCoords.x = static_cast<float>(x) / static_cast<float>(s);
				texCoords.y = static_cast<float>(z) / static_cast<float>(s);
				tracker++;
			}
			else
			{
				texCoords.x = static_cast<float>(x) / static_cast<float>(s);
				texCoords.y = static_cast<float>(z) / static_cast<float>(s);
				tracker = 0;
			}
			z++;
			m_TerrainInfo.texture.emplace_back(texCoords);
		}
	}

	void Terrain::GenerateVertexNormals(TerrainInformation& terrainInformation)
	{
		for (unsigned int z = 0; z < m_Size.x; ++z)
		{
			for (unsigned int x = 0; x < m_Size.x; ++x)
			{
				const glm::vec3& west = m_TerrainInfo.position[(x > 0 ? x - 1 : 0) + z * (int)m_Size.x];
				const glm::vec3& east = m_TerrainInfo.position[(x < (int)m_Size.x - 1 ? x + 1 : x) + z * (int)m_Size.x];

				glm::vec3 slope_x = east - west;

				const glm::vec3& south = m_TerrainInfo.position[x + (z > 0 ? z - 1 : 0) * (int)m_Size.x];
				const glm::vec3& north = m_TerrainInfo.position[x + (z < (int)m_Size.x - 1 ? z + 1 : z) * (int)m_Size.x];

				glm::vec3 slope_y = north - south;


				glm::vec3 normal = cross(slope_x, slope_y);
				glm::vec3 normalized = glm::normalize(normal);
				m_TerrainInfo.normal.push_back(normalized);
			}
		}
	}

	void Terrain::SmoothTerrain(TerrainInformation& terrainInformation)
	{
		for (int z = 0; z < m_Size.x; ++z)
		{
			for (int x = 0; x < m_Size.x; ++x)
			{
				float corners = (GetVertexHeight(x - 1, z - 1) +
						GetVertexHeight(x + 1, z - 1) +
						GetVertexHeight(x - 1, z + 1) +
						GetVertexHeight(x + 1, z + 1)) / 16.0f;

				float sides = (GetVertexHeight(x - 1, z) +
						GetVertexHeight(x + 1, z) +
						GetVertexHeight(x, z - 1) +
						GetVertexHeight(x, z + 1)) / 8.0f;

				float center = GetVertexHeight(x, z) / 4.0f;

				float newHeight = (corners + sides + center);

				if (newHeight > m_HighestPoint.y) { m_HighestPoint = glm::vec3(x, newHeight, z); }
				if (newHeight < m_LowestPoint.y) { m_LowestPoint = glm::vec3(x, newHeight, z); }

				SetVertexHeight(x, z, newHeight);
			}
		}
	}

}