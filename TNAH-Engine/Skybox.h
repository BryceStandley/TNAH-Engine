#pragma once
#include "TNAH/Core/Core.h"
#include <glm/glm.hpp>
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "TNAH/Renderer/Material.h"
#include <string>

namespace tnah {
	class Skybox {
	public: 
		Skybox();
		Skybox(const Texture3DProperties& skymapProperties);

	private:
		Ref<Texture3D> m_SkyboxTexture;
		Ref<VertexArray> m_VAO;
		Ref<VertexBuffer> m_VBO;
		BufferLayout m_BufferLayout;
		Ref<Material> m_Material;
		Texture3DProperties m_Sky;
		std::vector<float> m_VBOData;
		uint32_t m_VBOSize = 0;

	private:
		float* GetVBOData() { return &m_VBOData[0];}
		void Create();
		uint32_t GetVBODataSize() { return m_VBOSize; }

		friend class scene;
	};

	struct SkyboxComponent
	{
		Skybox* SceneSkybox;

		SkyboxComponent() = default;
		SkyboxComponent(const SkyboxComponent& other) = default;

		SkyboxComponent() 
		{
			SceneSkybox = new Skybox();
		}

		SkyboxComponent(const Texture3DProperties& skymapProperties)
		{}
	};
}