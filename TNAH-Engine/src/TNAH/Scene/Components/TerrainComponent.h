#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "TNAH/Renderer/Material.h"

namespace tnah {
	class Terrain
	{
	public:
		/*
		rp3d::CollisionBody* terrainCB;
		rp3d::RigidBody* terrainRB;
		rp3d::Collider* terrainCollider;
		float* terrainColliderHeightData;
		*/

		/**********************************************************************************************//**
		 * @fn	Terrain::Terrain() = default;
		 *
		 * @brief	Defaulted constructor, will construct a 100 square terrain with a min of 40 and a max of
		 * 			100 units.
		 *
		 * @author	Bryce Standley
		 * @date	23/07/2021
		 **************************************************************************************************/

		Terrain();
		Terrain(const int width, const int maxHeight, const int minHeight);
		Terrain(const std::string& heightmapFilePath);
		~Terrain();

		inline const glm::vec3 GetMaxHeight() { return m_HighestPoint; }
		inline const glm::vec3 GetMinHeight() { return m_LowestPoint; }

		inline const std::vector<glm::vec3> GetVertexPositions() { return m_TerrainInfo.position; }

		inline float* GetTotalData() { return &m_VBOData[0].x; }

		inline uint32_t* GetIndicesData() { return &m_IndicesData[0]; }

		inline const glm::vec2 GetSize() { return m_Size; }

		inline const float GetHeight(int x, int z);

		inline const float GetHeightColor(int x, int z);

		inline const float GetVertexHeight(int x, int z);

		inline const uint32_t GetTotalDataSize() { return m_VBOSize; }

		inline const uint32_t GetIndicesSize() { return m_IBOSize; }

		inline const BufferLayout GetBufferLayout() { return m_BufferLayout; }

		inline Ref<VertexArray> GetVertexArray() {return m_VAO;}
		inline Ref<VertexBuffer> GetVertexBuffer() {return m_VBO;}
		inline Ref<IndexBuffer> GetIndexBuffer() {return m_IBO;}
		inline Ref<Material> GetMaterial() {return m_Material;}

	private:
		/**********************************************************************************************//**
		 * @struct	TerrainInformation
		 *
		 * @brief	Information used to construct the terrain with textures and colours
		 *
		 * @author	Bryce Standley
		 * @date	23/07/2021
		 **************************************************************************************************/

		struct TerrainInformation
		{
			std::vector<glm::vec3> position;
			std::vector<glm::vec3> color;
			std::vector<glm::vec3> texture;
			std::vector<glm::vec3> normal;
		};

		void Create();

		void GenerateHeightmap(const int width, const int maxHeight, const int minHeight);

		bool LoadHeightField(const std::string& fileName);

		bool InBounds(int x, int z);

		void SetVertexHeight(int x, int z, const float newHeight);

		void GenerateVertexPositions(TerrainInformation& terrainInformation);

		void GenerateVertexIndices();

		void GenerateVertexColors(TerrainInformation& terrainInformaion);

		void GenerateVertexTextureCoords(TerrainInformation& terrainInformation);

		void GenerateVertexNormals(TerrainInformation& terrainInformation);

		void SmoothTerrain(TerrainInformation& terrainInformation);


	private:
		std::string m_HeightmapPath = "";
		
		float m_MinHeightmapHeight = 40.0f;
		float m_MaxHeightmapHeight = 100.0f;

		glm::vec2 m_Size = glm::vec2(0.0f);
		std::vector<float> m_TerrainHeights;
		float m_MinHeight = 0.0f;
		float m_MaxHeight = 0.0f;
		TerrainInformation m_TerrainInfo;

		/** @brief	Terrain information combined into a single vector for use in the vertex buffer*/
		std::vector<glm::vec3> m_VBOData;
		std::vector<uint32_t> m_IndicesData;
		uint32_t m_VBOSize;
		uint32_t m_IBOSize;
		BufferLayout m_BufferLayout;
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		Ref<IndexBuffer> m_IBO;
		Ref<Material> m_Material;
		std::vector<std::string> m_TextureFileNames;


		glm::vec3 m_HighestPoint = glm::vec3(0.0f);
		glm::vec3 m_LowestPoint = glm::vec3(0.0f);
		friend class EditorUI;
		friend class Serializer;
	};

	struct TerrainComponent
	{
		Terrain* SceneTerrain;

		TerrainComponent() = default;
		TerrainComponent(const TerrainComponent& other) = default;

		TerrainComponent(const std::string& heightMapFilePath)
		{
			SceneTerrain = new Terrain(heightMapFilePath);
		}

		TerrainComponent(const int width, const int maxHeight, const int minHeight)
		{
			SceneTerrain = new Terrain(width, maxHeight, minHeight);
		}

	};

}