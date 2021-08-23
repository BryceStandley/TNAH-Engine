#include <tnahpch.h>
#include "SkyboxComponent.h"

namespace tnah {
	
	Skybox::Skybox() 
	{
		Create();

		const std::string front = "front.jpg";
		const std::string back = "back.jpg";
		const std::string top = "top.jpg";
		const std::string bottom = "bottom.jpg";
		const std::string left = "left.jpg";
		const std::string right = "right.jpg";
		Texture3DProperties properties ={ front, back, left, right, top, bottom};
		Ref<Shader> shader;
		shader.reset(Shader::Create("Resources/shaders/default/skybox_vertex.glsl", "Resources/shaders/default/skybox_fragment.glsl"));
		m_Material.reset(SkyboxMaterial::Create(shader, properties));
		m_SkyboxTexture = m_Material->GetCubemapTextures();
		
		m_BufferLayout = { {ShaderDataType::Float3, "a_Position"} };

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(GetVBOData(), GetVBODataSize()));
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);
	}

	Skybox::Skybox(const Texture3DProperties& skyboxTextureProperties)
	{
		Create();
		Ref<Shader> shader;
		shader.reset(Shader::Create("Resources/shaders/default/skybox_vertex.glsl", "Resources/shaders/default/skybox_fragment.glsl"));
		m_Material.reset(SkyboxMaterial::Create(shader, skyboxTextureProperties));
		m_SkyboxTexture = m_Material->GetCubemapTextures();

		m_BufferLayout = { {ShaderDataType::Float3, "a_Position"} };

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(GetVBOData(), GetVBODataSize()));
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);
	}

	void Skybox::Create()
	{
		float skyBoxVertices[] = {
			// positions
			-1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
			1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

			-1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
			-1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

			1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

			-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
			1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f };

		m_VBOData.insert(m_VBOData.begin(), std::begin(skyBoxVertices), std::end(skyBoxVertices));

		m_VBOSize = (uint32_t)(sizeof(float) * m_VBOData.size());
	}



}