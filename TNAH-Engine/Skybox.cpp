#include "tnahpch.h"
#include "Skybox.h"

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


		m_Sky.Front = front;
		m_Sky.Back = back;
		m_Sky.Top = top;
		m_Sky.Bottom = bottom;
		m_Sky.Left = left;
		m_Sky.Right = right;

		m_SkyboxTexture.reset(Texture3D::Create(m_Sky));

		m_BufferLayout = { {ShaderDataType::Float3, "a_Position"} };

		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create(GetVBOData(), GetVBODataSize()));
		m_VBO->SetLayout(m_BufferLayout);
		m_VAO->AddVertexBuffer(m_VBO);

		m_Material.reset(Material::Create("Resources/shaders/default/skybox/skybox_vertex.glsl", "Resources/shaders/default/terrain/skybox_fragment.glsl"));

	}

	Skybox::Skybox(const Texture3DProperties& skymapProperties)
	{
		m_SkyboxTexture.reset(Texture3D::Create(skymapProperties));
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