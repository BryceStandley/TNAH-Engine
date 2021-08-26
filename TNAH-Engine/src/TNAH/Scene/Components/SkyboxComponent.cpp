#include <tnahpch.h>
#include "SkyboxComponent.h"

namespace tnah {
	
	Skybox::Skybox() 
	{
		Create();

		Texture3DProperties properties = {
		{"Resources/textures/skybox/bluecloud_ft.jpg"},
		{"Resources/textures/skybox/bluecloud_bk.jpg"},
		 {"Resources/textures/skybox/bluecloud_lf.jpg"},
		{"Resources/textures/skybox/bluecloud_rt.jpg"},
		{"Resources/textures/skybox/bluecloud_up.jpg"},
		{"Resources/textures/skybox/bluecloud_dn.jpg"}
		};
		
		Ref<Shader> shader;
		shader.reset(Shader::Create("Resources/shaders/default/skybox/skybox_vertex.glsl", "Resources/shaders/default/skybox/skybox_fragment.glsl"));
		m_Material.reset(SkyboxMaterial::Create(shader, properties));
		m_SkyboxTexture = m_Material->GetCubemapTextures();

		m_Material->BindShader();
		m_Material->GetShader()->SetInt("u_SkyboxTexture", m_SkyboxTexture->m_Slot);
		m_Material->UnBindShader();
		
		
		m_BufferLayout = { {ShaderDataType::Float3, "a_Position"} };

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(GetVBOData(), GetVBODataSize()));
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_VAO->SetIndexSize(36);
		
	}

	Skybox::Skybox(const Texture3DProperties& skyboxTextureProperties)
	{
		Create();
		Ref<Shader> shader;
		shader.reset(Shader::Create("Resources/shaders/default/skybox/skybox_vertex.glsl", "Resources/shaders/default/skybox/skybox_fragment.glsl"));
		m_Material.reset(SkyboxMaterial::Create(shader, skyboxTextureProperties));
		m_SkyboxTexture = m_Material->GetCubemapTextures();

		m_Material->BindShader();
		m_Material->GetShader()->SetInt("u_SkyboxTexture", 0);
		m_Material->UnBindShader();

		m_BufferLayout = { {ShaderDataType::Float3, "a_Position"} };

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(GetVBOData(), GetVBODataSize()));
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexSize(36);
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

		m_VBOSize = 3 * 36 * sizeof(float);
	}



}