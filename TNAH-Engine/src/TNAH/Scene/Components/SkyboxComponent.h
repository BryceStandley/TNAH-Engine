#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Material.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/Texture.h"

namespace tnah {
	class Skybox {

	public:
		Skybox();
		Skybox(const Texture3DProperties& skyboxTextureProperties);

		float* GetVBOData() { return &m_VBOData[0]; }
		uint32_t GetVBODataSize() { return m_VBOSize; }
		inline Ref<VertexArray> GetVertexArray() { return m_VAO; }
		inline Ref<VertexBuffer> GetVertexBuffer() { return m_VBO; }
		inline Ref<SkyboxMaterial> GetMaterial() { return m_Material; }


	private:
		
		void Create();
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		BufferLayout m_BufferLayout;
		
		Ref<SkyboxMaterial> m_Material;
		Ref<Texture3D> m_SkyboxTexture;
		
		std::vector<float> m_VBOData;
		uint32_t m_VBOSize = 0;

	private:
		friend class Scene;
		friend struct SkyboxComponent;
	};

	struct SkyboxComponent
	{
		Skybox* SceneSkybox;

		SkyboxComponent() 
		{
			SceneSkybox = new Skybox();
		}
		
		SkyboxComponent(const SkyboxComponent& other) = default;

		SkyboxComponent(const Texture3DProperties& cubemapProperties)
		{
			SceneSkybox = new Skybox(cubemapProperties);
		}
	};
}